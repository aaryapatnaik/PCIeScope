
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(void)
{
    DIR *dir = opendir("/sys/bus/pci/devices/");
    if (dir == NULL)
    {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    char path[512];
    unsigned int vendor, device, class_code;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.')
        {
            continue;
        }

        printf("\nPCI Device: %s\n", entry->d_name);

        const char *fields[] = {"vendor", "device", "class"};
        unsigned int *values[] = {&vendor, &device, &class_code};

        for (int i = 0; i < 3; i++)
        {
            int length = snprintf(path, sizeof(path),
                                  "/sys/bus/pci/devices/%s/%s",
                                  entry->d_name, fields[i]);

            if (length < 0 || (size_t)length >= sizeof(path))
            {
                fprintf(stderr, "PCI device path too long\n");
                closedir(dir);
                return 1;
            }

            FILE *file = fopen(path, "r");
            if (file == NULL)
            {
                perror(path);
                closedir(dir);
                return 1;
            }

            if (fscanf(file, "%x", values[i]) != 1)
            {
                fprintf(stderr, "Failed to read %s\n", path);
                fclose(file);
                closedir(dir);
                return 1;
            }

            fclose(file);
        }

        printf("  Vendor ID:  0x%04X\n", vendor);
        printf("  Device ID:  0x%04X\n", device);
        printf("  Class Code: 0x%06X\n", class_code);

        // Read PCI BAR/resource information
        int length = snprintf(path, sizeof(path),
                              "/sys/bus/pci/devices/%s/resource",
                              entry->d_name);

        if (length < 0 || (size_t)length >= sizeof(path))
        {
            fprintf(stderr, "PCI device path too long\n");
            closedir(dir);
            return 1;
        }

        FILE *resource = fopen(path, "r");

        if (resource != NULL)
        {
            unsigned long long start, end, flags;

            for (int bar = 0; bar < 6; bar++)
            {
                if (fscanf(resource, "%llx %llx %llx",
                           &start, &end, &flags) != 3)
                {
                    break;
                }

                if (start == 0 && end == 0 && flags == 0)
                {
                    continue;
                }

                printf("  BAR%d: 0x%llX - 0x%llX (%llu bytes)\n",
                       bar, start, end, end - start + 1);
            }

            fclose(resource);
        }

        // Read PCIe link information
        const char *link_fields[] = {
            "current_link_speed",
            "current_link_width",
            "max_link_speed",
            "max_link_width"};

        const char *link_labels[] = {
            "Current Link Speed",
            "Current Link Width",
            "Max Link Speed",
            "Max Link Width"};

        for (int i = 0; i < 4; i++)
        {
            int length = snprintf(path, sizeof(path),
                                  "/sys/bus/pci/devices/%s/%s",
                                  entry->d_name, link_fields[i]);

            if (length < 0 || (size_t)length >= sizeof(path))
            {
                fprintf(stderr, "PCI device path too long\n");
                closedir(dir);
                return 1;
            }

            FILE *link_file = fopen(path, "r");

            if (link_file == NULL)
            {
                printf("  %s: N/A\n", link_labels[i]);
                continue;
            }

            char value[128];

            if (fgets(value, sizeof(value), link_file) != NULL)
            {
                value[strcspn(value, "\n")] = '\0';
                printf("  %s: %s\n", link_labels[i], value);
            }
            else
            {
                printf("  %s: N/A\n", link_labels[i]);
            }

            fclose(link_file);
        }
    }

    closedir(dir);
    return 0;
}

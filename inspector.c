#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(void) {
    DIR *dir = opendir("/sys/bus/pci/devices/");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    char path[512];
    unsigned int vendor, device, class_code;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        printf("\nPCI Device: %s\n", entry->d_name);

        const char *fields[] = {"vendor", "device", "class"};
        unsigned int *values[] = {&vendor, &device, &class_code};

        for (int i = 0; i < 3; i++) {
            int length = snprintf(path, sizeof(path),
                      "/sys/bus/pci/devices/%s/%s",
                      entry->d_name, fields[i]);

            if (length < 0 || (size_t)length >= sizeof(path)) {
                fprintf(stderr, "PCI device path too long\n");
                closedir(dir);
                return 1;
            }

            FILE *file = fopen(path, "r");
            if (file == NULL) {
                perror(path);
                closedir(dir);
                return 1;
            }

            if (fscanf(file, "%x", values[i]) != 1) {
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
    }

    closedir(dir);
    return 0;
}
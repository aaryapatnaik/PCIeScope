
#include <stdio.h>

typedef enum
{
    DETECT,
    POLLING,
    CONFIGURATION,
    L0,
    RECOVERY
} LTSSM_State;

int main(void)
{
    LTSSM_State state = DETECT;
    int link_failure = 0;
    int recovered = 0;
    int running = 1;

    while (running)
    {
        switch (state)
        {
        case DETECT:
            printf("Detect -> Polling\n");
            state = POLLING;
            break;

        case POLLING:
            printf("Polling -> Configuration\n");
            state = CONFIGURATION;
            break;

        case CONFIGURATION:
            printf("Configuration -> L0\n");
            state = L0;
            break;

        case L0:
            if (!link_failure)
            {
                printf("Link established! State: L0\n");
                printf("Simulating link failure...\n");
                link_failure = 1;
                state = RECOVERY;
            }
            else if (recovered)
            {
                printf("Link restored! State: L0\n");
                running = 0;
            }
            break;

        case RECOVERY:
            printf("Recovery: Retraining link...\n");
            recovered = 1;
            state = L0;
            break;
        }
    }

    return 0;
}

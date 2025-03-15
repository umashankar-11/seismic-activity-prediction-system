#include <stdio.h>
#include <stdlib.h>

#define DATA_SIZE 30

typedef struct {
    int data[DATA_SIZE];
} SensorData;

void initializeData(SensorData *sensorData) {
    for (int i = 0; i < DATA_SIZE; i++) {
        if (rand() % 5 == 0) {
            sensorData->data[i] = -1;
        } else {
            sensorData->data[i] = rand() % 100;
        }
    }
}

void printData(SensorData *sensorData) {
    for (int i = 0; i < DATA_SIZE; i++) {
        if (sensorData->data[i] == -1) {
            printf("NaN ");
        } else {
            printf("%d ", sensorData->data[i]);
        }
    }
    printf("\n");
}

void meanImputation(SensorData *sensorData) {
    int sum = 0;
    int count = 0;

    for (int i = 0; i < DATA_SIZE; i++) {
        if (sensorData->data[i] != -1) {
            sum += sensorData->data[i];
            count++;
        }
    }

    int mean = (count > 0) ? sum / count : 0;

    for (int i = 0; i < DATA_SIZE; i++) {
        if (sensorData->data[i] == -1) {
            sensorData->data[i] = mean;
        }
    }
}

void linearInterpolation(SensorData *sensorData) {
    for (int i = 1; i < DATA_SIZE - 1; i++) {
        if (sensorData->data[i] == -1) {
            int j = i - 1;
            int k = i + 1;

            while (j >= 0 && sensorData->data[j] == -1) j--;
            while (k < DATA_SIZE && sensorData->data[k] == -1) k++;

            if (j >= 0 && k < DATA_SIZE) {
                int interpolatedValue = sensorData->data[j] + ((sensorData->data[k] - sensorData->data[j]) * (i - j)) / (k - j);
                sensorData->data[i] = interpolatedValue;
            }
        }
    }
}

void forwardFill(SensorData *sensorData) {
    for (int i = 1; i < DATA_SIZE; i++) {
        if (sensorData->data[i] == -1) {
            sensorData->data[i] = sensorData->data[i - 1];
        }
    }
}

void backwardFill(SensorData *sensorData) {
    for (int i = DATA_SIZE - 2; i >= 0; i--) {
        if (sensorData->data[i] == -1) {
            sensorData->data[i] = sensorData->data[i + 1];
        }
    }
}

int main() {
    SensorData sensorData;

    initializeData(&sensorData);

    printf("Original Data with Missing Values:\n");
    printData(&sensorData);

    printf("\nData after Mean Imputation:\n");
    meanImputation(&sensorData);
    printData(&sensorData);

    initializeData(&sensorData);
    printf("\nOriginal Data with Missing Values (Reinitialized):\n");
    printData(&sensorData);

    printf("\nData after Linear Interpolation:\n");
    linearInterpolation(&sensorData);
    printData(&sensorData);

    initializeData(&sensorData);
    printf("\nOriginal Data with Missing Values (Reinitialized):\n");
    printData(&sensorData);

    printf("\nData after Forward Fill Imputation:\n");
    forwardFill(&sensorData);
    printData(&sensorData);

    initializeData(&sensorData);
    printf("\nOriginal Data with Missing Values (Reinitialized):\n");
    printData(&sensorData);

    printf("\nData after Backward Fill Imputation:\n");
    backwardFill(&sensorData);
    printData(&sensorData);

    return 0;
}

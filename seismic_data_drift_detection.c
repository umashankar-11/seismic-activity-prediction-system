#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DATA_SIZE 100
#define THRESHOLD 0.05
#define DRIFT_WINDOW 10
#define NUM_DRIFT_DETECTIONS 5

typedef struct {
    float data[DATA_SIZE];
} SeismicData;

void initializeData(SeismicData *seismicData) {
    for (int i = 0; i < DATA_SIZE; i++) {
        seismicData->data[i] = (rand() % 2000) / 100.0; 
    }
}

void printData(SeismicData *seismicData) {
    for (int i = 0; i < DATA_SIZE; i++) {
        printf("%.2f ", seismicData->data[i]);
    }
    printf("\n");
}

float calculateMean(SeismicData *seismicData, int start, int end) {
    float sum = 0.0;
    for (int i = start; i <= end; i++) {
        sum += seismicData->data[i];
    }
    return sum / (end - start + 1);
}

float calculateStandardDeviation(SeismicData *seismicData, int start, int end, float mean) {
    float sum = 0.0;
    for (int i = start; i <= end; i++) {
        sum += (seismicData->data[i] - mean) * (seismicData->data[i] - mean);
    }
    return sqrt(sum / (end - start + 1));
}

int detectDrift(SeismicData *seismicData, int *driftStart, int *driftEnd) {
    int driftCount = 0;
    for (int i = DRIFT_WINDOW; i < DATA_SIZE; i++) {
        float mean1 = calculateMean(seismicData, i - DRIFT_WINDOW, i - 1);
        float mean2 = calculateMean(seismicData, i, i + DRIFT_WINDOW - 1);
        
        float stdDev1 = calculateStandardDeviation(seismicData, i - DRIFT_WINDOW, i - 1, mean1);
        float stdDev2 = calculateStandardDeviation(seismicData, i, i + DRIFT_WINDOW - 1, mean2);

        float difference = fabs(mean2 - mean1);
        
        if (difference > THRESHOLD && (stdDev1 > 0.5 || stdDev2 > 0.5)) {
            driftCount++;
            *driftStart = i - DRIFT_WINDOW;
            *driftEnd = i + DRIFT_WINDOW - 1;
            printf("Drift detected between indices %d and %d, Drift value: %.2f\n", *driftStart, *driftEnd, difference);
        }

        if (driftCount >= NUM_DRIFT_DETECTIONS) {
            return 1; 
        }
    }
    return 0;
}

void applyDriftCorrection(SeismicData *seismicData, int driftStart, int driftEnd) {
    for (int i = driftStart; i <= driftEnd; i++) {
        seismicData->data[i] = (seismicData->data[driftStart - 1] + seismicData->data[driftEnd + 1]) / 2;
    }
}

void applyAverageFilter(SeismicData *seismicData) {
    for (int i = 1; i < DATA_SIZE - 1; i++) {
        seismicData->data[i] = (seismicData->data[i - 1] + seismicData->data[i] + seismicData->data[i + 1]) / 3;
    }
}

void applyMedianFilter(SeismicData *seismicData) {
    float window[3];
    for (int i = 1; i < DATA_SIZE - 1; i++) {
        window[0] = seismicData->data[i - 1];
        window[1] = seismicData->data[i];
        window[2] = seismicData->data[i + 1];
        
        for (int j = 0; j < 2; j++) {
            for (int k = j + 1; k < 3; k++) {
                if (window[j] > window[k]) {
                    float temp = window[j];
                    window[j] = window[k];
                    window[k] = temp;
                }
            }
        }
        seismicData->data[i] = window[1]; 
    }
}

void applyExponentialSmoothing(SeismicData *seismicData, float alpha) {
    for (int i = 1; i < DATA_SIZE; i++) {
        seismicData->data[i] = alpha * seismicData->data[i] + (1 - alpha) * seismicData->data[i - 1];
    }
}

void resetDrift(SeismicData *seismicData) {
    for (int i = 0; i < DATA_SIZE; i++) {
        seismicData->data[i] = (rand() % 2000) / 100.0; 
    }
}

int main() {
    SeismicData seismicData;
    int driftStart = 0, driftEnd = 0;
    int driftDetected = 0;
    
    initializeData(&seismicData);

    printf("Original Seismic Data:\n");
    printData(&seismicData);

    driftDetected = detectDrift(&seismicData, &driftStart, &driftEnd);

    if (driftDetected) {
        printf("\nApplying Drift Correction:\n");
        applyDriftCorrection(&seismicData, driftStart, driftEnd);
        printData(&seismicData);
    } else {
        printf("\nNo Drift Detected.\n");
    }

    resetDrift(&seismicData);
    printf("\nSeismic Data After Reset:\n");
    printData(&seismicData);

    driftDetected = detectDrift(&seismicData, &driftStart, &driftEnd);
    if (driftDetected) {
        printf("\nApplying Drift Correction Again:\n");
        applyDriftCorrection(&seismicData, driftStart, driftEnd);
        printData(&seismicData);
    }

    applyAverageFilter(&seismicData);
    printf("\nSeismic Data After Average Filter:\n");
    printData(&seismicData);

    resetDrift(&seismicData);
    printf("\nSeismic Data After Reset (Before Median Filter):\n");
    printData(&seismicData);

    applyMedianFilter(&seismicData);
    printf("\nSeismic Data After Median Filter:\n");
    printData(&seismicData);

    resetDrift(&seismicData);
    printf("\nSeismic Data After Reset (Before Exponential Smoothing):\n");
    printData(&seismicData);

    applyExponentialSmoothing(&seismicData, 0.5);
    printf("\nSeismic Data After Exponential Smoothing:\n");
    printData(&seismicData);

    return 0;
}

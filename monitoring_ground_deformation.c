#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SAMPLES 1000
#define THRESHOLD 0.05
#define SAMPLING_INTERVAL 1 
#define FILTER_WINDOW 5

typedef struct {
    double timestamp;
    double displacement;
} GroundDeformationSample;

GroundDeformationSample data[MAX_SAMPLES];
int dataIndex = 0;

double getSensorReading() {
    return (rand() % 100) / 100.0;
}

void calibrateSensor() {
    printf("Calibrating sensor...\n");
}

void recordData() {
    if (dataIndex < MAX_SAMPLES) {
        double displacement = getSensorReading();
        double timestamp = dataIndex * SAMPLING_INTERVAL;

        data[dataIndex].timestamp = timestamp;
        data[dataIndex].displacement = displacement;
        dataIndex++;
    } else {
        printf("Data storage full\n");
    }
}

int checkForDeformation(double displacement) {
    if (displacement > THRESHOLD) {
        return 1;
    }
    return 0;
}

void analyzeData() {
    printf("Analyzing stored data...\n");
    for (int i = 0; i < dataIndex; i++) {
        if (checkForDeformation(data[i].displacement)) {
            printf("Deformation detected at timestamp %.2f with displacement %.2f\n",
                   data[i].timestamp, data[i].displacement);
        }
    }
}

double calculateAverageDisplacement() {
    double sum = 0;
    for (int i = 0; i < dataIndex; i++) {
        sum += data[i].displacement;
    }
    return sum / dataIndex;
}

void performStatistics() {
    double average = calculateAverageDisplacement();
    printf("Average displacement: %.2f\n", average);

    double sumOfSquares = 0;
    for (int i = 0; i < dataIndex; i++) {
        sumOfSquares += pow(data[i].displacement - average, 2);
    }
    double variance = sumOfSquares / dataIndex;
    double stdDev = sqrt(variance);
    printf("Standard deviation: %.2f\n", stdDev);
}

void resetData() {
    dataIndex = 0;
    printf("Data collection reset.\n");
}

double filterData() {
    double filteredValue = 0;
    int count = 0;
    for (int i = dataIndex - FILTER_WINDOW; i < dataIndex; i++) {
        if (i >= 0) {
            filteredValue += data[i].displacement;
            count++;
        }
    }
    return (count > 0) ? filteredValue / count : 0;
}

void logDataToFile() {
    FILE *file = fopen("deformation_log.txt", "a");
    if (file != NULL) {
        for (int i = 0; i < dataIndex; i++) {
            fprintf(file, "Timestamp: %.2f, Displacement: %.2f\n",
                    data[i].timestamp, data[i].displacement);
        }
        fclose(file);
    } else {
        printf("Error opening log file.\n");
    }
}

void sendAlert(double displacement) {
    if (displacement > THRESHOLD) {
        printf("ALERT: Significant ground deformation detected! Displacement: %.2f\n", displacement);
    }
}

int main() {
    printf("Ground deformation monitoring system started.\n");
    calibrateSensor();

    for (int i = 0; i < 50; i++) {
        recordData();
        printf("Recorded data at timestamp %.2f: Displacement = %.2f\n",
               data[dataIndex-1].timestamp, data[dataIndex-1].displacement);

        if (checkForDeformation(data[dataIndex-1].displacement)) {
            printf("Warning: Significant ground deformation detected!\n");
        }

        if (i % 10 == 0) {
            analyzeData();
        }

        if (i % 5 == 0) {
            double filteredDisplacement = filterData();
            printf("Filtered displacement at timestamp %.2f: %.2f\n",
                   data[dataIndex-1].timestamp, filteredDisplacement);
        }

        logDataToFile();
        sendAlert(data[dataIndex-1].displacement);
    }

    performStatistics();
    resetData();

    return 0;
}

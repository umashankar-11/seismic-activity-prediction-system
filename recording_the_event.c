#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SAMPLES 1000
#define SAMPLING_INTERVAL 1 
#define FILTER_WINDOW 5
#define SEISMIC_THRESHOLD 0.10 
#define PREDICTION_THRESHOLD 0.20 
#define ALERT_THRESHOLD 0.25 
#define DYNAMIC_THRESHOLD_ADJUSTMENT 0.02
#define MULTI_SENSOR_COUNT 3 

typedef struct {
    double timestamp;
    double displacement;
    double acceleration;  
    double sensorData[MULTI_SENSOR_COUNT]; 
} SeismicActivitySample;

SeismicActivitySample data[MAX_SAMPLES];
int dataIndex = 0;
double ALERT_THRESHOLD = SEISMIC_THRESHOLD;

double getSeismicSensorReading() {
    return (rand() % 100) / 100.0; 
}

void calibrateSensor() {
    printf("Calibrating seismic sensor...\n");
}

void recordData() {
    if (dataIndex < MAX_SAMPLES) {
        double displacement = getSeismicSensorReading();
        double acceleration = (rand() % 100) / 100.0;
        double timestamp = dataIndex * SAMPLING_INTERVAL;

        data[dataIndex].timestamp = timestamp;
        data[dataIndex].displacement = displacement;
        data[dataIndex].acceleration = acceleration;

        
        for (int i = 0; i < MULTI_SENSOR_COUNT; i++) {
            data[dataIndex].sensorData[i] = (rand() % 100) / 100.0;
        }

        dataIndex++;
    } else {
        printf("Data storage full\n");
    }
}

int checkForSeismicEvent(double displacement) {
    if (displacement > ALERT_THRESHOLD) {
        return 1;
    }
    return 0;
}

void analyzeSeismicData() {
    printf("Analyzing seismic data...\n");
    for (int i = 0; i < dataIndex; i++) {
        if (checkForSeismicEvent(data[i].displacement)) {
            printf("Seismic event detected at timestamp %.2f with displacement %.2f\n",
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

void adjustThreshold() {
    double averageDisplacement = calculateAverageDisplacement();
    if (averageDisplacement > ALERT_THRESHOLD) {
        ALERT_THRESHOLD += DYNAMIC_THRESHOLD_ADJUSTMENT;
        printf("Threshold adjusted to: %.2f\n", ALERT_THRESHOLD);
    }
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
    FILE *file = fopen("seismic_activity_log.txt", "a");
    if (file != NULL) {
        for (int i = 0; i < dataIndex; i++) {
            fprintf(file, "Timestamp: %.2f, Displacement: %.2f, Acceleration: %.2f\n",
                    data[i].timestamp, data[i].displacement, data[i].acceleration);
        }
        fclose(file);
    } else {
        printf("Error opening log file.\n");
    }
}

void sendAlert(double displacement) {
    if (displacement > PREDICTION_THRESHOLD) {
        printf("ALERT: Potential seismic event predicted! Displacement: %.2f\n", displacement);
    }
}

void movingAverageFilter(int windowSize) {
    double sum = 0;
    int count = 0;
    for (int i = dataIndex - windowSize; i < dataIndex; i++) {
        if (i >= 0) {
            sum += data[i].displacement;
            count++;
        }
    }
    printf("Moving average: %.2f\n", (count > 0) ? sum / count : 0);
}

void monitorSeismicActivity() {
    printf("Monitoring seismic activity...\n");

    for (int i = 0; i < 50; i++) {
        recordData();
        printf("Recorded seismic data at timestamp %.2f: Displacement = %.2f, Acceleration = %.2f\n",
               data[dataIndex-1].timestamp, data[dataIndex-1].displacement, data[dataIndex-1].acceleration);

        if (checkForSeismicEvent(data[dataIndex-1].displacement)) {
            printf("Warning: Significant seismic displacement detected!\n");
        }

        if (i % 10 == 0) {
            analyzeSeismicData();
        }

        if (i % 5 == 0) {
            double filteredDisplacement = filterData();
            printf("Filtered seismic displacement at timestamp %.2f: %.2f\n",
                   data[dataIndex-1].timestamp, filteredDisplacement);
        }

        logDataToFile();
        sendAlert(data[dataIndex-1].displacement);

        if (i % 15 == 0) {
            adjustThreshold();
        }

        if (i % 7 == 0) {
            movingAverageFilter(3);
        }
    }

    printf("Seismic monitoring completed.\n");
    analyzeSeismicData();
}

int main() {
    printf("Seismic activity prediction system started.\n");
    calibrateSensor();

    monitorSeismicActivity();

    return 0;
}

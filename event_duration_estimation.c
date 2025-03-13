#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SAMPLES 1000
#define SAMPLING_INTERVAL 1 
#define SEISMIC_THRESHOLD 0.15 
#define EVENT_DURATION_THRESHOLD 0.05 
#define ALERT_THRESHOLD 0.20 
#define MOVING_AVERAGE_WINDOW 5 
#define MULTI_SENSOR_COUNT 3 

typedef struct {
    double timestamp;
    double displacement;
    double acceleration;
    double sensorData[MULTI_SENSOR_COUNT];
} SeismicData;

SeismicData seismicData[MAX_SAMPLES];
int dataIndex = 0;
int eventStartIdx = -1;
int eventEndIdx = -1;
int eventInProgress = 0;
int totalSeismicEvents = 0;

double generateSeismicReading() {
    return (rand() % 100) / 100.0; 
}

void initializeSeismicSystem() {
    printf("Initializing seismic system...\n");
}

void logSeismicEvent(double timestamp, double displacement, double acceleration) {
    printf("Logging seismic data: Timestamp: %.2f, Displacement: %.2f, Acceleration: %.2f\n",
           timestamp, displacement, acceleration);
}

int isSeismicEventTriggered(double displacement) {
    return displacement > SEISMIC_THRESHOLD;
}

void startEvent(int idx) {
    if (!eventInProgress) {
        eventStartIdx = idx;
        eventInProgress = 1;
        printf("Seismic event started at timestamp %.2f\n", seismicData[idx].timestamp);
    }
}

void endEvent(int idx) {
    if (eventInProgress) {
        eventEndIdx = idx;
        eventInProgress = 0;
        double duration = seismicData[eventEndIdx].timestamp - seismicData[eventStartIdx].timestamp;
        printf("Seismic event ended at timestamp %.2f\n", seismicData[idx].timestamp);
        printf("Event duration: %.2f seconds\n", duration);
        totalSeismicEvents++;
    }
}

void triggerAlert(double displacement) {
    if (displacement > ALERT_THRESHOLD) {
        printf("ALERT: Significant seismic activity detected! Displacement: %.2f\n", displacement);
    }
}

double calculateMovingAverage(int windowSize) {
    double sum = 0;
    int count = 0;
    for (int i = dataIndex - windowSize; i < dataIndex; i++) {
        if (i >= 0) {
            sum += seismicData[i].displacement;
            count++;
        }
    }
    return (count > 0) ? sum / count : 0;
}

void recordSeismicData() {
    if (dataIndex < MAX_SAMPLES) {
        double displacement = generateSeismicReading();
        double acceleration = (rand() % 100) / 100.0;
        double timestamp = dataIndex * SAMPLING_INTERVAL;

        seismicData[dataIndex].timestamp = timestamp;
        seismicData[dataIndex].displacement = displacement;
        seismicData[dataIndex].acceleration = acceleration;

        
        for (int i = 0; i < MULTI_SENSOR_COUNT; i++) {
            seismicData[dataIndex].sensorData[i] = (rand() % 100) / 100.0;
        }

        logSeismicEvent(timestamp, displacement, acceleration);

        dataIndex++;
    } else {
        printf("Seismic data storage full.\n");
    }
}

void evaluateSeismicEventDuration() {
    for (int i = 0; i < dataIndex; i++) {
        double displacement = seismicData[i].displacement;

        if (isSeismicEventTriggered(displacement)) {
            if (!eventInProgress) {
                startEvent(i);
            }
        } else {
            if (eventInProgress && (i - eventStartIdx >= EVENT_DURATION_THRESHOLD)) {
                endEvent(i);
            }
        }

        triggerAlert(displacement);
    }
}

void saveSeismicDataToFile() {
    FILE *file = fopen("seismic_activity_log.txt", "a");
    if (file != NULL) {
        for (int i = 0; i < dataIndex; i++) {
            fprintf(file, "Timestamp: %.2f, Displacement: %.2f, Acceleration: %.2f\n",
                    seismicData[i].timestamp, seismicData[i].displacement, seismicData[i].acceleration);
        }
        fclose(file);
    } else {
        printf("Error opening file for logging seismic data.\n");
    }
}

void calculateSeismicEventFrequency() {
    printf("Total seismic events detected: %d\n", totalSeismicEvents);
}

void estimateEventSeverity(double displacement) {
    if (displacement > SEISMIC_THRESHOLD) {
        printf("Event severity: High (Magnitude: %.2f)\n", displacement);
    } else {
        printf("Event severity: Low (Magnitude: %.2f)\n", displacement);
    }
}

void generateSimulatedGraph() {
    
    printf("Generating simulated graph of seismic displacement...\n");
    for (int i = 0; i < dataIndex; i++) {
        printf("Time: %.2f, Displacement: %.2f\n", seismicData[i].timestamp, seismicData[i].displacement);
    }
}

void processSeismicData() {
    printf("Processing seismic data...\n");
    evaluateSeismicEventDuration();
    calculateSeismicEventFrequency();
}

void monitorSeismicActivity() {
    printf("Starting seismic activity monitoring...\n");

    for (int i = 0; i < 50; i++) {
        recordSeismicData();

        if (i % 10 == 0) {
            processSeismicData();
        }

        if (i % 5 == 0) {
            saveSeismicDataToFile();
        }

        if (i % 7 == 0) {
            double movingAverage = calculateMovingAverage(MOVING_AVERAGE_WINDOW);
            printf("Moving Average (last %d samples): %.2f\n", MOVING_AVERAGE_WINDOW, movingAverage);
        }

        estimateEventSeverity(seismicData[dataIndex-1].displacement);
    }

    generateSimulatedGraph();
    printf("Seismic monitoring completed.\n");
}

int main() {
    initializeSeismicSystem();

    monitorSeismicActivity();

    return 0;
}

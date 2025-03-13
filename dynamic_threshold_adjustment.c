#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SAMPLES 1000
#define SAMPLING_INTERVAL 1 
#define INITIAL_THRESHOLD 0.2 
#define EVENT_DURATION_THRESHOLD 0.05 
#define NUM_SENSORS 3 

typedef struct {
    double timestamp;
    double displacement;
    double acceleration;
} SensorData;

typedef struct {
    SensorData data[MAX_SAMPLES];
    int dataIndex;
    double threshold;
    char sensorName[20];
} SeismicSensor;

SeismicSensor sensors[NUM_SENSORS];
int eventStartIdx = -1;
int eventEndIdx = -1;
int eventInProgress = 0;
int totalSeismicEvents = 0;
int globalSampleIndex = 0;

double generateSensorReading() {
    return (rand() % 100) / 100.0;
}

void initializeSensor(SeismicSensor *sensor, const char *sensorName, double threshold) {
    sensor->dataIndex = 0;
    sensor->threshold = threshold;
    snprintf(sensor->sensorName, sizeof(sensor->sensorName), "%s", sensorName);
    printf("Initializing sensor: %s with threshold: %.2f\n", sensor->sensorName, threshold);
}

void logSensorData(SeismicSensor *sensor, double timestamp) {
    printf("Sensor %s data at Timestamp %.2f\n", sensor->sensorName, timestamp);
    printf("Displacement: %.2f, Acceleration: %.2f\n", sensor->data[sensor->dataIndex].displacement, sensor->data[sensor->dataIndex].acceleration);
}

int isSeismicEventTriggered(double displacement, double threshold) {
    return displacement > threshold;
}

void startEvent(int idx) {
    if (!eventInProgress) {
        eventStartIdx = idx;
        eventInProgress = 1;
        printf("Seismic event started at timestamp %.2f\n", sensors[0].data[idx].timestamp);
    }
}

void endEvent(int idx) {
    if (eventInProgress) {
        eventEndIdx = idx;
        eventInProgress = 0;
        double duration = sensors[0].data[eventEndIdx].timestamp - sensors[0].data[eventStartIdx].timestamp;
        printf("Seismic event ended at timestamp %.2f\n", sensors[0].data[idx].timestamp);
        printf("Event duration: %.2f seconds\n", duration);
        totalSeismicEvents++;
    }
}

void adjustThresholdBasedOnHistory(SeismicSensor *sensor) {
    double averageDisplacement = 0;
    for (int i = 0; i < sensor->dataIndex; i++) {
        averageDisplacement += sensor->data[i].displacement;
    }

    averageDisplacement /= sensor->dataIndex;

    double newThreshold = averageDisplacement * 1.2;
    if (newThreshold > sensor->threshold) {
        printf("Adjusting threshold for %s to %.2f\n", sensor->sensorName, newThreshold);
        sensor->threshold = newThreshold;
    }
}

void recordSensorData(SeismicSensor *sensor) {
    if (sensor->dataIndex < MAX_SAMPLES) {
        double displacement = generateSensorReading();
        double acceleration = generateSensorReading();
        double timestamp = sensor->dataIndex * SAMPLING_INTERVAL;

        sensor->data[sensor->dataIndex].timestamp = timestamp;
        sensor->data[sensor->dataIndex].displacement = displacement;
        sensor->data[sensor->dataIndex].acceleration = acceleration;

        logSensorData(sensor, timestamp);
        sensor->dataIndex++;
    } else {
        printf("Sensor %s data storage full.\n", sensor->sensorName);
    }
}

void evaluateSeismicEventDuration() {
    for (int i = 0; i < sensors[0].dataIndex; i++) {
        double displacement = 0;
        for (int j = 0; j < NUM_SENSORS; j++) {
            displacement += sensors[j].data[i].displacement;
        }
        displacement /= NUM_SENSORS;

        for (int j = 0; j < NUM_SENSORS; j++) {
            if (isSeismicEventTriggered(displacement, sensors[j].threshold)) {
                if (!eventInProgress) {
                    startEvent(i);
                }
                break;
            } else {
                if (eventInProgress && (i - eventStartIdx >= EVENT_DURATION_THRESHOLD)) {
                    endEvent(i);
                }
            }
        }
    }
}

void saveSeismicDataToFile() {
    FILE *file = fopen("seismic_activity_log.txt", "a");
    if (file != NULL) {
        for (int j = 0; j < NUM_SENSORS; j++) {
            for (int i = 0; i < sensors[j].dataIndex; i++) {
                fprintf(file, "Sensor %s - Timestamp: %.2f, Displacement: %.2f, Acceleration: %.2f\n",
                        sensors[j].sensorName, sensors[j].data[i].timestamp,
                        sensors[j].data[i].displacement, sensors[j].data[i].acceleration);
            }
        }
        fclose(file);
    } else {
        printf("Error opening file for logging seismic data.\n");
    }
}

void processSeismicData() {
    printf("Processing seismic data...\n");
    for (int i = 0; i < NUM_SENSORS; i++) {
        adjustThresholdBasedOnHistory(&sensors[i]);
    }
    evaluateSeismicEventDuration();
    printf("Total seismic events detected: %d\n", totalSeismicEvents);
}

void monitorSeismicActivity() {
    printf("Starting seismic activity monitoring...\n");

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < NUM_SENSORS; j++) {
            recordSensorData(&sensors[j]);
        }

        if (i % 10 == 0) {
            processSeismicData();
        }

        if (i % 5 == 0) {
            saveSeismicDataToFile();
        }
    }

    printf("Seismic monitoring completed.\n");
}

int main() {
    initializeSensor(&sensors[0], "Sensor 1", INITIAL_THRESHOLD);
    initializeSensor(&sensors[1], "Sensor 2", INITIAL_THRESHOLD);
    initializeSensor(&sensors[2], "Sensor 3", INITIAL_THRESHOLD);

    monitorSeismicActivity();

    return 0;
}

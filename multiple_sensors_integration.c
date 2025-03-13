#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SAMPLES 1000
#define SAMPLING_INTERVAL 1 
#define SEISMIC_THRESHOLD 0.2 
#define EVENT_DURATION_THRESHOLD 0.05 
#define NUM_SENSORS 5 

typedef struct {
    double timestamp;
    double displacement;
    double acceleration;
    double sensorSpecificData;
} SensorData;

typedef struct {
    SensorData sensorData[MAX_SAMPLES];
    int dataIndex;
    double calibrationFactor; 
    char sensorName[20];
} SeismicSensor;

SeismicSensor sensors[NUM_SENSORS];
int eventStartIdx = -1;
int eventEndIdx = -1;
int eventInProgress = 0;
int totalSeismicEvents = 0;

double generateSensorReading() {
    return (rand() % 100) / 100.0;
}

void initializeSensor(SeismicSensor *sensor, const char *sensorName, double calibrationFactor) {
    sensor->dataIndex = 0;
    sensor->calibrationFactor = calibrationFactor;
    snprintf(sensor->sensorName, sizeof(sensor->sensorName), "%s", sensorName);
    printf("Initializing sensor: %s with calibration factor: %.2f\n", sensor->sensorName, calibrationFactor);
}

void logSensorData(SeismicSensor *sensor, double timestamp) {
    printf("Sensor %s data at Timestamp %.2f\n", sensor->sensorName, timestamp);
    printf("Displacement: %.2f, Acceleration: %.2f, Sensor Specific Data: %.2f\n",
            sensor->sensorData[sensor->dataIndex].displacement,
            sensor->sensorData[sensor->dataIndex].acceleration,
            sensor->sensorData[sensor->dataIndex].sensorSpecificData);
}

int isSeismicEventTriggered(double displacement) {
    return displacement > SEISMIC_THRESHOLD;
}

void startEvent(int idx) {
    if (!eventInProgress) {
        eventStartIdx = idx;
        eventInProgress = 1;
        printf("Seismic event started at timestamp %.2f\n", sensors[0].sensorData[idx].timestamp);
    }
}

void endEvent(int idx) {
    if (eventInProgress) {
        eventEndIdx = idx;
        eventInProgress = 0;
        double duration = sensors[0].sensorData[eventEndIdx].timestamp - sensors[0].sensorData[eventStartIdx].timestamp;
        printf("Seismic event ended at timestamp %.2f\n", sensors[0].sensorData[idx].timestamp);
        printf("Event duration: %.2f seconds\n", duration);
        totalSeismicEvents++;
    }
}

void recordSensorData(SeismicSensor *sensor) {
    if (sensor->dataIndex < MAX_SAMPLES) {
        double displacement = generateSensorReading() * sensor->calibrationFactor;
        double acceleration = generateSensorReading();
        double sensorSpecificData = generateSensorReading();
        double timestamp = sensor->dataIndex * SAMPLING_INTERVAL;

        sensor->sensorData[sensor->dataIndex].timestamp = timestamp;
        sensor->sensorData[sensor->dataIndex].displacement = displacement;
        sensor->sensorData[sensor->dataIndex].acceleration = acceleration;
        sensor->sensorData[sensor->dataIndex].sensorSpecificData = sensorSpecificData;

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
            displacement += sensors[j].sensorData[i].displacement;
        }
        displacement /= NUM_SENSORS;

        if (isSeismicEventTriggered(displacement)) {
            if (!eventInProgress) {
                startEvent(i);
            }
        } else {
            if (eventInProgress && (i - eventStartIdx >= EVENT_DURATION_THRESHOLD)) {
                endEvent(i);
            }
        }
    }
}

void saveSeismicDataToFile() {
    FILE *file = fopen("seismic_activity_log.txt", "a");
    if (file != NULL) {
        for (int j = 0; j < NUM_SENSORS; j++) {
            for (int i = 0; i < sensors[j].dataIndex; i++) {
                fprintf(file, "Sensor %s - Timestamp: %.2f, Displacement: %.2f, Acceleration: %.2f, Sensor Specific Data: %.2f\n",
                        sensors[j].sensorName, sensors[j].sensorData[i].timestamp,
                        sensors[j].sensorData[i].displacement, sensors[j].sensorData[i].acceleration,
                        sensors[j].sensorData[i].sensorSpecificData);
            }
        }
        fclose(file);
    } else {
        printf("Error opening file for logging seismic data.\n");
    }
}

void processSeismicData() {
    printf("Processing seismic data...\n");
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
    
    initializeSensor(&sensors[0], "Sensor 1", 1.0);
    initializeSensor(&sensors[1], "Sensor 2", 1.2);
    initializeSensor(&sensors[2], "Sensor 3", 0.8);
    initializeSensor(&sensors[3], "Sensor 4", 1.1);
    initializeSensor(&sensors[4], "Sensor 5", 1.0);

    monitorSeismicActivity();

    return 0;
}

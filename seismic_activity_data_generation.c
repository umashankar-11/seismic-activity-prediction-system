#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_SAMPLES 1000
#define SAMPLING_INTERVAL 1 
#define SEISMIC_THRESHOLD 0.5
#define NUM_SENSORS 3

typedef struct {
    double timestamp;
    double displacement;
    double acceleration;
} SensorData;

typedef struct SeismicSensor SeismicSensor;

struct SeismicSensor {
    SensorData data[MAX_SAMPLES];
    int dataIndex;
    char sensorName[20];
    void (*generateData)(SeismicSensor *sensor);
    double (*calculateActivity)(SeismicSensor *sensor);
};

void genericGenerateData(SeismicSensor *sensor) {
    if (sensor->dataIndex < MAX_SAMPLES) {
        sensor->data[sensor->dataIndex].timestamp = sensor->dataIndex * SAMPLING_INTERVAL;
        sensor->data[sensor->dataIndex].displacement = (rand() % 1000) / 1000.0;
        sensor->data[sensor->dataIndex].acceleration = (rand() % 1000) / 1000.0;
        sensor->dataIndex++;
    }
}

double genericCalculateActivity(SeismicSensor *sensor) {
    double totalActivity = 0;
    for (int i = 0; i < sensor->dataIndex; i++) {
        totalActivity += sensor->data[i].displacement;
    }
    return totalActivity / sensor->dataIndex;
}

void typeAGenerateData(SeismicSensor *sensor) {
    if (sensor->dataIndex < MAX_SAMPLES) {
        sensor->data[sensor->dataIndex].timestamp = sensor->dataIndex * SAMPLING_INTERVAL;
        sensor->data[sensor->dataIndex].displacement = (rand() % 500) / 1000.0;
        sensor->data[sensor->dataIndex].acceleration = (rand() % 800) / 1000.0;
        sensor->dataIndex++;
    }
}

double typeACalculateActivity(SeismicSensor *sensor) {
    double activity = 0;
    for (int i = 0; i < sensor->dataIndex; i++) {
        activity += sensor->data[i].displacement * 1.1;
    }
    return activity / sensor->dataIndex;
}

void typeBGenerateData(SeismicSensor *sensor) {
    if (sensor->dataIndex < MAX_SAMPLES) {
        sensor->data[sensor->dataIndex].timestamp = sensor->dataIndex * SAMPLING_INTERVAL;
        sensor->data[sensor->dataIndex].displacement = (rand() % 1000) / 1000.0;
        sensor->data[sensor->dataIndex].acceleration = (rand() % 600) / 1000.0;
        sensor->dataIndex++;
    }
}

double typeBCalculateActivity(SeismicSensor *sensor) {
    double activity = 0;
    for (int i = 0; i < sensor->dataIndex; i++) {
        activity += sensor->data[i].acceleration * 1.2;
    }
    return activity / sensor->dataIndex;
}

void initializeSensor(SeismicSensor *sensor, const char *name, void (*generateFunc)(SeismicSensor *), double (*calculateFunc)(SeismicSensor *)) {
    sensor->dataIndex = 0;
    snprintf(sensor->sensorName, sizeof(sensor->sensorName), "%s", name);
    sensor->generateData = generateFunc;
    sensor->calculateActivity = calculateFunc;
}

int detectSeismicEvent(double activityLevel) {
    return (activityLevel > SEISMIC_THRESHOLD);
}

void logSensorData(SeismicSensor *sensor) {
    for (int i = 0; i < sensor->dataIndex; i++) {
        printf("Sensor: %s | Timestamp: %.2f | Displacement: %.3f | Acceleration: %.3f\n",
               sensor->sensorName, sensor->data[i].timestamp, sensor->data[i].displacement, sensor->data[i].acceleration);
    }
}

void processSeismicData(SeismicSensor *sensor) {
    for (int i = 0; i < 50; i++) {
        sensor->generateData(sensor);
        double activityLevel = sensor->calculateActivity(sensor);
        if (detectSeismicEvent(activityLevel)) {
            printf("Seismic event detected by %s at Timestamp %.2f with activity level %.3f\n",
                   sensor->sensorName, sensor->data[i].timestamp, activityLevel);
        }
    }
}

void saveDataToFile(SeismicSensor *sensor) {
    FILE *file = fopen("seismic_activity_log.txt", "a");
    if (file) {
        for (int i = 0; i < sensor->dataIndex; i++) {
            fprintf(file, "Sensor: %s | Timestamp: %.2f | Displacement: %.3f | Acceleration: %.3f\n",
                    sensor->sensorName, sensor->data[i].timestamp, sensor->data[i].displacement, sensor->data[i].acceleration);
        }
        fclose(file);
    } else {
        printf("Error opening file for logging data.\n");
    }
}

void monitorSeismicSensors() {
    SeismicSensor sensors[NUM_SENSORS];
    initializeSensor(&sensors[0], "Sensor Type A", typeAGenerateData, typeACalculateActivity);
    initializeSensor(&sensors[1], "Sensor Type B", typeBGenerateData, typeBCalculateActivity);
    initializeSensor(&sensors[2], "Generic Sensor", genericGenerateData, genericCalculateActivity);

    for (int i = 0; i < NUM_SENSORS; i++) {
        processSeismicData(&sensors[i]);
        saveDataToFile(&sensors[i]);
    }
}

int main() {
    monitorSeismicSensors();
    return 0;
}

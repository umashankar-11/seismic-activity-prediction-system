#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DATA_POINTS 1000
#define MAX_SENSOR_COUNT 50
#define MAX_READINGS_PER_SENSOR 100

typedef struct {
    float strain_values[MAX_READINGS_PER_SENSOR];
    int data_count;
    float max_strain;
    float min_strain;
    float average_strain;
} SensorData;

typedef struct {
    int sensor_id;
    SensorData sensor_data;
    bool high_stress_alert;
} Sensor;

typedef struct {
    Sensor sensors[MAX_SENSOR_COUNT];
    int sensor_count;
} StressMonitoringSystem;

void initializeSystem(StressMonitoringSystem *system);
void collectStrainData(Sensor *sensor, float strain_value);
void processStrainData(Sensor *sensor);
void evaluateStressAlert(Sensor *sensor);
void printSensorData(Sensor *sensor);
void simulateStressCollection(StressMonitoringSystem *system);
void printSystemStatus(StressMonitoringSystem *system);
void clearSystemData(StressMonitoringSystem *system);
void resetSensorData(Sensor *sensor);

int main(void) {
    StressMonitoringSystem system;
    initializeSystem(&system);

    simulateStressCollection(&system);
    printSystemStatus(&system);

    return 0;
}

void initializeSystem(StressMonitoringSystem *system) {
    system->sensor_count = MAX_SENSOR_COUNT;
    for (int i = 0; i < system->sensor_count; i++) {
        system->sensors[i].sensor_id = i + 1;
        resetSensorData(&system->sensors[i]);
    }
}

void resetSensorData(Sensor *sensor) {
    sensor->sensor_data.data_count = 0;
    sensor->sensor_data.max_strain = -1.0;
    sensor->sensor_data.min_strain = 1000.0;
    sensor->sensor_data.average_strain = 0.0;
    sensor->high_stress_alert = false;
}

void collectStrainData(Sensor *sensor, float strain_value) {
    if (sensor->sensor_data.data_count < MAX_READINGS_PER_SENSOR) {
        sensor->sensor_data.strain_values[sensor->sensor_data.data_count] = strain_value;
        sensor->sensor_data.data_count++;
    }
}

void processStrainData(Sensor *sensor) {
    float sum = 0.0;
    sensor->sensor_data.max_strain = -1.0;
    sensor->sensor_data.min_strain = 1000.0;

    for (int i = 0; i < sensor->sensor_data.data_count; i++) {
        float strain = sensor->sensor_data.strain_values[i];
        sum += strain;

        if (strain > sensor->sensor_data.max_strain) {
            sensor->sensor_data.max_strain = strain;
        }
        if (strain < sensor->sensor_data.min_strain) {
            sensor->sensor_data.min_strain = strain;
        }
    }

    sensor->sensor_data.average_strain = sum / sensor->sensor_data.data_count;
}

void evaluateStressAlert(Sensor *sensor) {
    if (sensor->sensor_data.max_strain > 5.0) { 
        sensor->high_stress_alert = true;
    } else {
        sensor->high_stress_alert = false;
    }
}

void printSensorData(Sensor *sensor) {
    printf("Sensor ID: %d\n", sensor->sensor_id);
    printf("Max Strain: %.2f\n", sensor->sensor_data.max_strain);
    printf("Min Strain: %.2f\n", sensor->sensor_data.min_strain);
    printf("Average Strain: %.2f\n", sensor->sensor_data.average_strain);
    printf("High Stress Alert: %s\n", sensor->high_stress_alert ? "YES" : "NO");
    printf("stress\n");
}

void simulateStressCollection(StressMonitoringSystem *system) {
    for (int i = 0; i < system->sensor_count; i++) {
        for (int j = 0; j < MAX_READINGS_PER_SENSOR; j++) {
            float simulated_strain = ((rand() % 100) / 10.0) - 5.0; 
            collectStrainData(&system->sensors[i], simulated_strain);
        }
        processStrainData(&system->sensors[i]);
        evaluateStressAlert(&system->sensors[i]);
    }
}

void printSystemStatus(StressMonitoringSystem *system) {
    for (int i = 0; i < system->sensor_count; i++) {
        printSensorData(&system->sensors[i]);
    }
}

void clearSystemData(StressMonitoringSystem *system) {
    for (int i = 0; i < system->sensor_count; i++) {
        resetSensorData(&system->sensors[i]);
    }
}

void simulateStressData(Sensor *sensor) {
    for (int i = 0; i < MAX_READINGS_PER_SENSOR; i++) {
        collectStrainData(sensor, ((rand() % 100) / 10.0) - 5.0);
    }
    processStrainData(sensor);
    evaluateStressAlert(sensor);
}

void resetSystem(StressMonitoringSystem *system) {
    clearSystemData(system);
}

void resetSensor(Sensor *sensor) {
    resetSensorData(sensor);
}

void simulateHighStressEvent(Sensor *sensor) {
    for (int i = 0; i < MAX_READINGS_PER_SENSOR; i++) {
        collectStrainData(sensor, 10.0); 
    }
    processStrainData(sensor);
    evaluateStressAlert(sensor);
}

void evaluateSystemStress(StressMonitoringSystem *system) {
    bool system_stress_alert = false;

    for (int i = 0; i < system->sensor_count; i++) {
        if (system->sensors[i].high_stress_alert) {
            system_stress_alert = true;
        }
    }

    if (system_stress_alert) {
        printf("Warning: High Stress Alert in the system!\n");
    } else {
        printf("System is stable.\n");
    }
}

void simulateStressDistribution(StressMonitoringSystem *system) {
    for (int i = 0; i < system->sensor_count; i++) {
        float simulated_stress = ((rand() % 100) / 10.0) - 3.0;
        collectStrainData(&system->sensors[i], simulated_stress);
    }
    printSystemStatus(system);
}

void performStressTest(Sensor *sensor) {
    for (int i = 0; i < MAX_READINGS_PER_SENSOR; i++) {
        collectStrainData(sensor, 7.5); 
    }
    processStrainData(sensor);
    evaluateStressAlert(sensor);
    printSensorData(sensor);
}

void evaluateAndPrintSensorStatus(Sensor *sensor) {
    processStrainData(sensor);
    evaluateStressAlert(sensor);
    printSensorData(sensor);
}

void updateSensorData(Sensor *sensor, float *new_strain_values, int count) {
    for (int i = 0; i < count && i < MAX_READINGS_PER_SENSOR; i++) {
        collectStrainData(sensor, new_strain_values[i]);
    }
    processStrainData(sensor);
    evaluateStressAlert(sensor);
}

void collectAndProcessStressData(StressMonitoringSystem *system) {
    for (int i = 0; i < system->sensor_count; i++) {
        simulateStressData(&system->sensors[i]);
    }
    printSystemStatus(system);
}

void stressTestSystem(StressMonitoringSystem *system) {
    for (int i = 0; i < system->sensor_count; i++) {
        simulateStressCollection(system);
    }
    evaluateSystemStress(system);
}

void resetSensorDataAfterTest(Sensor *sensor) {
    resetSensor(sensor);
}

void simulateCriticalStress(Sensor *sensor) {
    for (int i = 0; i < MAX_READINGS_PER_SENSOR; i++) {
        collectStrainData(sensor, 8.0); 
    }
    processStrainData(sensor);
    evaluateStressAlert(sensor);
    printSensorData(sensor);
}

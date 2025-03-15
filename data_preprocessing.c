#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define DATA_SIZE 20
#define MIN_VALUE 0
#define MAX_VALUE 100

typedef struct {
    int value;
    int rawValue;
    int normalizedValue;
} SensorData;


void generateRandomData(SensorData *data, int size) {
    for (int i = 0; i < size; i++) {
        data[i].rawValue = rand() % (MAX_VALUE + 1); 
        data[i].value = data[i].rawValue;
    }
}

void printData(SensorData *data, int size) {
    for (int i = 0; i < size; i++) {
        printf("Data Point %d - Raw Value: %d, Processed Value: %d, Normalized Value: %d\n", 
               i + 1, data[i].rawValue, data[i].value, data[i].normalizedValue);
    }
}


void filterData(SensorData *data, int size, int minValue, int maxValue) {
    for (int i = 0; i < size; i++) {
        if (data[i].rawValue < minValue) {
            data[i].value = minValue; 
        } else if (data[i].rawValue > maxValue) {
            data[i].value = maxValue; 
        } else {
            data[i].value = data[i].rawValue; 
        }
    }
}

void normalizeData(SensorData *data, int size) {
    int min = data[0].value;
    int max = data[0].value;

    for (int i = 1; i < size; i++) {
        if (data[i].value < min) {
            min = data[i].value;
        }
        if (data[i].value > max) {
            max = data[i].value;
        }
    }

    for (int i = 0; i < size; i++) {
        data[i].normalizedValue = (data[i].value - min) * 100 / (max - min);
    }
}

double calculateMean(SensorData *data, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i].value;
    }
    return (double)sum / size;
}

double calculateStdDev(SensorData *data, int size, double mean) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += pow(data[i].value - mean, 2);
    }
    return sqrt(sum / size);
}


void detectOutliers(SensorData *data, int size, double mean, double stdDev) {
    double threshold = mean + 2 * stdDev; 
    for (int i = 0; i < size; i++) {
        if (data[i].value > threshold) {
            printf("Outlier detected at index %d: %d\n", i, data[i].value);
            data[i].value = threshold; 
        }
    }
}

void removeOutliers(SensorData *data, int size, int thresholdValue) {
    for (int i = 0; i < size; i++) {
        if (data[i].value > thresholdValue) {
            printf("Removing outlier at index %d: %d\n", i, data[i].value);
            data[i].value = thresholdValue; 
        }
    }
}

void extractFeatures(SensorData *data, int size) {
    double mean = calculateMean(data, size);
    double stdDev = calculateStdDev(data, size, mean);

    printf("Mean of the data: %.2f\n", mean);
    printf("Standard Deviation of the data: %.2f\n", stdDev);
}

void applyMovingAverage(SensorData *data, int size, int windowSize) {
    int *smoothedData = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        int sum = 0;
        int count = 0;
        
        
        for (int j = i - windowSize / 2; j <= i + windowSize / 2; j++) {
            if (j >= 0 && j < size) {
                sum += data[j].value;
                count++;
            }
        }
        
        smoothedData[i] = sum / count;
    }

    
    for (int i = 0; i < size; i++) {
        data[i].value = smoothedData[i];
    }

    free(smoothedData);
}


void preprocessData(SensorData *data, int size) {
    
    filterData(data, size, MIN_VALUE, MAX_VALUE);

    normalizeData(data, size);

    double mean = calculateMean(data, size);
    double stdDev = calculateStdDev(data, size, mean);
    
    extractFeatures(data, size);

    detectOutliers(data, size, mean, stdDev);
    removeOutliers(data, size, MAX_VALUE);
    
    applyMovingAverage(data, size, 3);
}

int main() {
    SensorData data[DATA_SIZE];
    
    generateRandomData(data, DATA_SIZE);
    
    printf("Initial Data:\n");
    printData(data, DATA_SIZE);
    
    printf("\nPreprocessing Data...\n");
    preprocessData(data, DATA_SIZE);
    
    printf("\nPreprocessed Data:\n");
    printData(data, DATA_SIZE);

    return 0;
}

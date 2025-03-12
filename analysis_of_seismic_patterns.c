#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SEISMIC_SENSOR_ADDRESS 0xA0
#define THRESHOLD 50
#define ADC_RESOLUTION 1024
#define ADC_MAX_VOLTAGE 3.3
#define SIMULATION_COUNT 1000
#define SEISMIC_NOISE_LEVEL 10
#define MAX_EVENT_LOGS 50
#define MOVING_AVERAGE_WINDOW 5
#define PEAK_DETECTION_THRESHOLD 0.8
#define EVENT_ANALYSIS_WINDOW 10

typedef struct {
    uint16_t raw_value;
    float magnitude;
    float timestamp;
} SeismicData;

typedef struct {
    SeismicData event_data[MAX_EVENT_LOGS];
    int event_count;
} EventLog;

typedef struct {
    float readings[MOVING_AVERAGE_WINDOW];
    int index;
    float sum;
} MovingAverage;

typedef struct {
    SeismicData data[EVENT_ANALYSIS_WINDOW];
    int index;
} EventAnalysis;

void generate_seismic_data(SeismicData *data);
void process_seismic_data(SeismicData *data);
bool is_significant_event(SeismicData *data);
void print_seismic_data(SeismicData *data);
void simulate_seismic_activity(EventLog *log, MovingAverage *ma, EventAnalysis *ea);
void log_event(EventLog *log, SeismicData *data);
float get_random_noise();
void delay_ms(int ms);
void print_separator();
void display_event_log(EventLog *log);
void reset_event_log(EventLog *log);
void print_summary(int event_count);
void initialize_moving_average(MovingAverage *ma);
void update_moving_average(MovingAverage *ma, float value);
float get_moving_average(MovingAverage *ma);
void initialize_event_analysis(EventAnalysis *ea);
void update_event_analysis(EventAnalysis *ea, SeismicData *data);
bool is_peak_event(SeismicData *data, MovingAverage *ma, EventAnalysis *ea);
void analyze_event_patterns(EventLog *log);

void generate_seismic_data(SeismicData *data) {
    data->raw_value = rand() % ADC_RESOLUTION;
    data->magnitude = (float)data->raw_value / ADC_RESOLUTION * ADC_MAX_VOLTAGE;
    data->timestamp = (float)time(NULL);
}

void process_seismic_data(SeismicData *data) {
    data->magnitude += get_random_noise();
}

bool is_significant_event(SeismicData *data) {
    if (data->magnitude > THRESHOLD) {
        return true;
    }
    return false;
}

void print_seismic_data(SeismicData *data) {
    printf("Timestamp: %.0f sec | Raw Value: %d | Magnitude: %.2f V\n", 
            data->timestamp, data->raw_value, data->magnitude);
}

void simulate_seismic_activity(EventLog *log, MovingAverage *ma, EventAnalysis *ea) {
    SeismicData data;
    int event_count = 0;
    
    printf("Seismic Activity Monitoring System\n");
    print_separator();
    
    for (int i = 0; i < SIMULATION_COUNT; i++) {
        generate_seismic_data(&data);
        process_seismic_data(&data);
        print_seismic_data(&data);

        update_moving_average(ma, data.magnitude);
        
        if (is_significant_event(&data)) {
            printf("---- Significant Event Detected ----\n");
            log_event(log, &data);
            event_count++;
        }

        update_event_analysis(ea, &data);

        if (is_peak_event(&data, ma, ea)) {
            printf("---- Peak Event Detected ----\n");
        }
        
        delay_ms(500);
    }

    print_summary(event_count);
    display_event_log(log);
    reset_event_log(log);
    analyze_event_patterns(log);
}

void log_event(EventLog *log, SeismicData *data) {
    if (log->event_count < MAX_EVENT_LOGS) {
        log->event_data[log->event_count] = *data;
        log->event_count++;
    } else {
        printf("Event Log Full!\n");
    }
}

float get_random_noise() {
    return ((float)(rand() % (SEISMIC_NOISE_LEVEL * 2)) - SEISMIC_NOISE_LEVEL) / 100.0f;
}

void delay_ms(int ms) {
    for (int i = 0; i < ms * 1000; i++);
}

void print_separator() {
    printf("seismic activity prediction\n");
}

void display_event_log(EventLog *log) {
    if (log->event_count == 0) {
        printf("No events to display.\n");
    } else {
        printf("\nEvent Log:\n");
        print_separator();
        for (int i = 0; i < log->event_count; i++) {
            printf("Event %d: Timestamp: %.0f sec | Magnitude: %.2f V\n", 
                   i + 1, log->event_data[i].timestamp, log->event_data[i].magnitude);
        }
        print_separator();
    }
}

void reset_event_log(EventLog *log) {
    log->event_count = 0;
}

void print_summary(int event_count) {
    printf("\nTotal Significant Events Detected: %d\n", event_count);
    print_separator();
}

void initialize_moving_average(MovingAverage *ma) {
    ma->index = 0;
    ma->sum = 0.0f;
    for (int i = 0; i < MOVING_AVERAGE_WINDOW; i++) {
        ma->readings[i] = 0.0f;
    }
}

void update_moving_average(MovingAverage *ma, float value) {
    ma->sum -= ma->readings[ma->index];
    ma->readings[ma->index] = value;
    ma->sum += value;
    ma->index = (ma->index + 1) % MOVING_AVERAGE_WINDOW;
}

float get_moving_average(MovingAverage *ma) {
    return ma->sum / MOVING_AVERAGE_WINDOW;
}

void initialize_event_analysis(EventAnalysis *ea) {
    ea->index = 0;
    for (int i = 0; i < EVENT_ANALYSIS_WINDOW; i++) {
        ea->data[i].magnitude = 0.0f;
    }
}

void update_event_analysis(EventAnalysis *ea, SeismicData *data) {
    ea->data[ea->index] = *data;
    ea->index = (ea->index + 1) % EVENT_ANALYSIS_WINDOW;
}

bool is_peak_event(SeismicData *data, MovingAverage *ma, EventAnalysis *ea) {
    if (data->magnitude > get_moving_average(ma) * PEAK_DETECTION_THRESHOLD) {
        return true;
    }
    return false;
}

void analyze_event_patterns(EventLog *log) {
    printf("\nAnalyzing Seismic Event Patterns...\n");
    print_separator();
    
    for (int i = 1; i < log->event_count; i++) {
        float time_diff = log->event_data[i].timestamp - log->event_data[i-1].timestamp;
        if (time_diff < 1.0f) {  
            printf("Cluster Detected: Event %d and Event %d are clustered!\n", i, i+1);
        }
    }
    
    for (int i = 0; i < log->event_count; i++) {
        if (log->event_data[i].magnitude > PEAK_DETECTION_THRESHOLD) {
            printf("Peak Event Detected: Event %d with Magnitude: %.2f V\n", i+1, log->event_data[i].magnitude);
        }
    }

    print_separator();
}

int main() {
    srand((unsigned int)time(NULL));
    EventLog log = {0};
    MovingAverage ma;
    EventAnalysis ea;
    
    initialize_moving_average(&ma);
    initialize_event_analysis(&ea);
    
    simulate_seismic_activity(&log, &ma, &ea);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_EVENTS 200
#define THRESHOLD_MIN 50
#define THRESHOLD_MAX 90
#define PREDICTION_WINDOW 10
#define WARNING_THRESHOLD 80
#define SEISMIC_NOISE 10
#define ADC_MAX 1024
#define SEISMIC_ALERT_LEVEL_1 50
#define SEISMIC_ALERT_LEVEL_2 75
#define SEISMIC_ALERT_LEVEL_3 90

typedef enum {
    MILD,
    MODERATE,
    SEVERE
} EventCategory;

typedef struct {
    float magnitude;
    float timestamp;
    EventCategory category;
} Event;

typedef struct {
    Event events[MAX_EVENTS];
    int count;
} EventLog;

typedef struct {
    float values[PREDICTION_WINDOW];
    int idx;
} PredictionModel;

typedef struct {
    float risk;
    float prediction;
    int alert_level;
} WarningSystem;

void generate_event(Event *event);
void add_event(EventLog *log, Event *event);
void process_event(Event *event);
EventCategory categorize_event(float magnitude);
int is_significant_event(Event *event);
void update_prediction_model(PredictionModel *model, float value);
float predict_activity(PredictionModel *model);
float calculate_risk(EventLog *log);
void send_warning(const char *message);
void display_warning(float risk, float prediction, int alert_level);
void simulate_seismic_activity(EventLog *log, PredictionModel *model, WarningSystem *ws);
void adjust_thresholds(EventLog *log);
void display_event_log(EventLog *log);

int main() {
    srand((unsigned int)time(NULL));
    
    EventLog log = {0};
    PredictionModel model = {0};
    WarningSystem ws = {0};
    
    printf("Seismic Prediction and Warning System\n");
    
    simulate_seismic_activity(&log, &model, &ws);
    
    return 0;
}

void generate_event(Event *event) {
    event->magnitude = (rand() % ADC_MAX) / 10.0f;
    event->timestamp = (float)time(NULL);
    event->category = categorize_event(event->magnitude);
}

void add_event(EventLog *log, Event *event) {
    if (log->count < MAX_EVENTS) {
        log->events[log->count] = *event;
        log->count++;
    } else {
        printf("Event log full!\n");
    }
}

void process_event(Event *event) {
    event->magnitude += (rand() % SEISMIC_NOISE) / 100.0f;
}

EventCategory categorize_event(float magnitude) {
    if (magnitude < SEISMIC_ALERT_LEVEL_1) {
        return MILD;
    } else if (magnitude < SEISMIC_ALERT_LEVEL_2) {
        return MODERATE;
    } else {
        return SEVERE;
    }
}

int is_significant_event(Event *event) {
    return event->magnitude > THRESHOLD_MIN;
}

void update_prediction_model(PredictionModel *model, float value) {
    model->values[model->idx] = value;
    model->idx = (model->idx + 1) % PREDICTION_WINDOW;
}

float predict_activity(PredictionModel *model) {
    float sum = 0.0f;
    for (int i = 0; i < PREDICTION_WINDOW; i++) {
        sum += model->values[i];
    }
    return sum / PREDICTION_WINDOW;
}

float calculate_risk(EventLog *log) {
    float total = 0.0f;
    for (int i = 0; i < log->count; i++) {
        total += log->events[i].magnitude;
    }
    return total / log->count;
}

void send_warning(const char *message) {
    printf("Sending warning: %s\n", message);
}

void display_warning(float risk, float prediction, int alert_level) {
    if (risk > WARNING_THRESHOLD) {
        send_warning("High seismic risk detected!");
    }
    if (prediction > WARNING_THRESHOLD) {
        send_warning("Prediction indicates high seismic activity!");
    }

    switch (alert_level) {
        case MILD:
            printf("Event is categorized as MILD.\n");
            break;
        case MODERATE:
            printf("Event is categorized as MODERATE.\n");
            break;
        case SEVERE:
            printf("Event is categorized as SEVERE. Immediate action required!\n");
            break;
        default:
            break;
    }
}

void simulate_seismic_activity(EventLog *log, PredictionModel *model, WarningSystem *ws) {
    Event event;
    int events_processed = 0;
    
    while (events_processed < 1000) {
        generate_event(&event);
        process_event(&event);
        
        if (is_significant_event(&event)) {
            add_event(log, &event);
            printf("Significant event detected: %.2f magnitude\n", event.magnitude);
        }
        
        update_prediction_model(model, event.magnitude);
        
        ws->prediction = predict_activity(model);
        ws->risk = calculate_risk(log);
        ws->alert_level = event.category;
        
        display_warning(ws->risk, ws->prediction, ws->alert_level);
        
        events_processed++;
        
        adjust_thresholds(log);
    }

    display_event_log(log);
}

void adjust_thresholds(EventLog *log) {
    if (log->count > 0) {
        float avg_magnitude = calculate_risk(log);
        if (avg_magnitude > 75) {
            printf("Threshold adjusted: High average seismic activity, setting THRESHOLD_MAX to 95.\n");
        } else {
            printf("Threshold adjusted: Normal seismic activity, setting THRESHOLD_MAX to 90.\n");
        }
    }
}

void display_event_log(EventLog *log) {
    printf("\nEvent Log Summary:\n");
    for (int i = 0; i < log->count; i++) {
        printf("Event %d - Timestamp: %.0f | Magnitude: %.2f | Category: %d\n", 
               i + 1, log->events[i].timestamp, log->events[i].magnitude, log->events[i].category);
    }
}

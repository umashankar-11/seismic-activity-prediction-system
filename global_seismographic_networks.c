#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATIONS 100
#define MAX_EVENT_RECORDS 500
#define MAX_SEISMIC_DATA_POINTS 1000

typedef struct {
    float latitude;
    float longitude;
    float depth;      
    float magnitude;   
    char date[11];    
    char time[9];     
    bool event_detected;
} SeismicEvent;

typedef struct {
    int station_id;
    char location[50];
    SeismicEvent events[MAX_EVENT_RECORDS];
    int event_count;
} SeismicStation;

typedef struct {
    SeismicStation stations[MAX_STATIONS];
    int station_count;
} SeismicNetwork;

void initializeSeismicNetwork(SeismicNetwork *network);
void initializeStation(SeismicStation *station, int station_id, const char *location);
void recordSeismicEvent(SeismicStation *station, SeismicEvent *event);
void processSeismicData(SeismicStation *station);
void generateSeismicAlert(SeismicStation *station, SeismicEvent *event);
void printSeismicEvent(SeismicEvent *event);
void simulateSeismicActivity(SeismicNetwork *network);
void printSeismicNetworkStatus(SeismicNetwork *network);
void analyzeSeismicData(SeismicNetwork *network);
void analyzeEventImpact(SeismicEvent *event);
void resetStationData(SeismicStation *station);
void printSeismicStationData(SeismicStation *station);
void resetNetwork(SeismicNetwork *network);
void printSeismicAlert(SeismicEvent *event);
void handleSeismicAlert(SeismicEvent *event);
void simulateGlobalSeismicActivity(SeismicNetwork *network);
void analyzeGlobalSeismicRisk(SeismicNetwork *network);
void simulateEventBasedOnMagnitude(SeismicEvent *event);

int main(void) {
    SeismicNetwork network;
    initializeSeismicNetwork(&network);

    simulateSeismicActivity(&network);
    printSeismicNetworkStatus(&network);
    analyzeSeismicData(&network);
    analyzeGlobalSeismicRisk(&network);

    return 0;
}

void initializeSeismicNetwork(SeismicNetwork *network) {
    network->station_count = MAX_STATIONS;
    for (int i = 0; i < network->station_count; i++) {
        char location[50];
        sprintf(location, "Station %d Location", i + 1);
        initializeStation(&network->stations[i], i + 1, location);
    }
}

void initializeStation(SeismicStation *station, int station_id, const char *location) {
    station->station_id = station_id;
    strcpy(station->location, location);
    station->event_count = 0;
}

void recordSeismicEvent(SeismicStation *station, SeismicEvent *event) {
    if (station->event_count < MAX_EVENT_RECORDS) {
        station->events[station->event_count] = *event;
        station->event_count++;
    }
}

void processSeismicData(SeismicStation *station) {
    for (int i = 0; i < station->event_count; i++) {
        SeismicEvent *event = &station->events[i];
        if (event->event_detected) {
            generateSeismicAlert(station, event);
        }
    }
}

void generateSeismicAlert(SeismicStation *station, SeismicEvent *event) {
    if (event->magnitude >= 6.0) {
        printSeismicAlert(event);
    }
}

void printSeismicEvent(SeismicEvent *event) {
    printf("Event Date: %s\n", event->date);
    printf("Event Time: %s\n", event->time);
    printf("Location: Lat: %.2f, Long: %.2f, Depth: %.2f km\n", event->latitude, event->longitude, event->depth);
    printf("Magnitude: %.2f\n", event->magnitude);
    printf("Event Detected: %s\n", event->event_detected ? "YES" : "NO");
    printf("global network\n");
}

void simulateSeismicActivity(SeismicNetwork *network) {
    for (int i = 0; i < network->station_count; i++) {
        for (int j = 0; j < 10; j++) {
            SeismicEvent event;
            event.latitude = (rand() % 180) - 90;  
            event.longitude = (rand() % 360) - 180; 
            event.depth = rand() % 700;  
            event.magnitude = (rand() % 10) + 4;  
            snprintf(event.date, sizeof(event.date), "2025-03-%02d", j + 1);
            snprintf(event.time, sizeof(event.time), "12:00:%02d", j * 5);
            event.event_detected = (rand() % 2) == 0 ? true : false;  

            recordSeismicEvent(&network->stations[i], &event);
        }
        processSeismicData(&network->stations[i]);
    }
}

void printSeismicNetworkStatus(SeismicNetwork *network) {
    for (int i = 0; i < network->station_count; i++) {
        printf("Seismic Station ID: %d\n", network->stations[i].station_id);
        printSeismicStationData(&network->stations[i]);
    }
}

void analyzeSeismicData(SeismicNetwork *network) {
    for (int i = 0; i < network->station_count; i++) {
        SeismicStation *station = &network->stations[i];
        for (int j = 0; j < station->event_count; j++) {
            SeismicEvent *event = &station->events[j];
            analyzeEventImpact(event);
        }
    }
}

void analyzeEventImpact(SeismicEvent *event) {
    if (event->magnitude >= 7.0) {
        printf("High Impact Event Detected!\n");
        printSeismicEvent(event);
    } else if (event->magnitude >= 5.0) {
        printf("Moderate Impact Event Detected.\n");
        printSeismicEvent(event);
    } else {
        printf("Low Impact Event.\n");
        printSeismicEvent(event);
    }
}

void resetStationData(SeismicStation *station) {
    station->event_count = 0;
}

void printSeismicStationData(SeismicStation *station) {
    printf("Station Location: %s\n", station->location);
    printf("Total Events Recorded: %d\n", station->event_count);
    printf("---- Event Details ----\n");
    for (int i = 0; i < station->event_count; i++) {
        printSeismicEvent(&station->events[i]);
    }
}

void resetNetwork(SeismicNetwork *network) {
    for (int i = 0; i < network->station_count; i++) {
        resetStationData(&network->stations[i]);
    }
}

void printSeismicAlert(SeismicEvent *event) {
    printf("ALERT: Seismic Event Detected!\n");
    printf("Location: Lat: %.2f, Long: %.2f, Depth: %.2f km\n", event->latitude, event->longitude, event->depth);
    printf("Magnitude: %.2f\n", event->magnitude);
    printf("Time: %s, Date: %s\n", event->time, event->date);
    printf("---- ALERT ----\n");
}

void handleSeismicAlert(SeismicEvent *event) {
    if (event->magnitude > 6.0) {
        printf("Critical Alert: Potential earthquake detected. Immediate action required!\n");
    }
}

void simulateGlobalSeismicActivity(SeismicNetwork *network) {
    for (int i = 0; i < network->station_count; i++) {
        simulateSeismicActivity(network);
    }
}

void analyzeGlobalSeismicRisk(SeismicNetwork *network) {
    int total_events = 0;
    for (int i = 0; i < network->station_count; i++) {
        total_events += network->stations[i].event_count;
    }
    printf("Total Seismic Events in Network: %d\n", total_events);
    if (total_events > 50) {
        printf("High Seismic Risk Across Network!\n");
    } else {
        printf("Seismic Activity is within Normal Range.\n");
    }
}

void simulateEventBasedOnMagnitude(SeismicEvent *event) {
    event->magnitude = (rand() % 10) + 4;  
    event->latitude = (rand() % 180) - 90;
    event->longitude = (rand() % 360) - 180;
    event->depth = rand() % 700;
    snprintf(event->date, sizeof(event->date), "2025-03-01");
    snprintf(event->time, sizeof(event->time), "14:00:00");
    event->event_detected = (rand() % 2) == 0;
}

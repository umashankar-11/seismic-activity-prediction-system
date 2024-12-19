#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif


#define MAX_EVENTS 10000
#define MAGNITUDE_THRESHOLD 5.0
#define PREDICTION_WINDOW 7 
#define BUFFER_SIZE 1024
#define LOG_FILE "seismic_events.txt"


typedef struct {
    float magnitude;
    char location[256];
    time_t timestamp;
} SeismicEvent;


SeismicEvent seismic_events[MAX_EVENTS];
int event_count = 0;


void log_seismic_event(float magnitude, const char *location);
void record_seismic_event(float magnitude, const char *location);
void analyze_seismic_activity();
void make_prediction();
void generate_random_seismic_data();
float generate_random_magnitude(float min, float max);
void get_random_location(char *location, int length);
void print_event(SeismicEvent *event);
void write_logs_to_file();
void read_logs_from_file();


int main() {
    srand(time(NULL));
    read_logs_from_file();  // Read previously logged data from file

   
    for (int i = 0; i < 500; i++) {
        generate_random_seismic_data();
        sleep(1);  // Simulate delay between seismic events
    }

    
    analyze_seismic_activity();

    
    make_prediction();

    return 0;
}


void log_seismic_event(float magnitude, const char *location) {
    if (event_count < MAX_EVENTS) {
        seismic_events[event_count].magnitude = magnitude;
        strncpy(seismic_events[event_count].location, location, sizeof(seismic_events[event_count].location) - 1);
        seismic_events[event_count].timestamp = time(NULL);

        event_count++;

        
        FILE *log_file = fopen(LOG_FILE, "a");
        if (log_file != NULL) {
            fprintf(log_file, "%.2f %s %ld\n", magnitude, location, seismic_events[event_count - 1].timestamp);
            fclose(log_file);
        }
    }
}


void record_seismic_event(float magnitude, const char *location) {
    log_seismic_event(magnitude, location);
    printf("Recorded Seismic Event: Magnitude=%.2f, Location=%s\n", magnitude, location);
}


void analyze_seismic_activity() {
    int high_magnitude_count = 0;
    int total_events = 0;

    for (int i = 0; i < event_count; i++) {
        if (seismic_events[i].magnitude >= MAGNITUDE_THRESHOLD) {
            high_magnitude_count++;
        }
        total_events++;
    }

    printf("\n--- Seismic Activity Analysis ---\n");
    printf("Total Events: %d\n", total_events);
    printf("High Magnitude Events (>= %.2f): %d\n", MAGNITUDE_THRESHOLD, high_magnitude_count);
    printf("Percentage of High Magnitude Events: %.2f%%\n", ((float)high_magnitude_count / total_events) * 100);
}


void make_prediction() {
    int high_magnitude_count = 0;
    int recent_events = 0;

    time_t current_time = time(NULL);
    for (int i = event_count - 1; i >= 0; i--) {
        // Consider events within the last 'PREDICTION_WINDOW' days
        if (difftime(current_time, seismic_events[i].timestamp) <= (PREDICTION_WINDOW * 24 * 60 * 60)) {
            recent_events++;
            if (seismic_events[i].magnitude >= MAGNITUDE_THRESHOLD) {
                high_magnitude_count++;
            }
        }
    }

    printf("\n--- Earthquake Prediction ---\n");
    if (recent_events == 0) {
        printf("Not enough recent data to make a prediction.\n");
    } else {
        printf("Recent Events within the last %d days: %d\n", PREDICTION_WINDOW, recent_events);
        printf("High Magnitude Events: %d\n", high_magnitude_count);
        printf("Prediction: ");
        if (high_magnitude_count >= (recent_events / 2)) {
            printf("A strong earthquake is more likely in the coming days!\n");
        } else {
            printf("No strong earthquake expected soon.\n");
        }
    }
}


void generate_random_seismic_data() {
    float magnitude = generate_random_magnitude(4.0, 9.0);  // Random magnitude between 4.0 and 9.0
    char location[256];
    get_random_location(location, sizeof(location));  // Get random location

    record_seismic_event(magnitude, location);
}

// Function to generate random magnitude within a given range
float generate_random_magnitude(float min, float max) {
    return min + (rand() / (RAND_MAX / (max - min)));
}

// Function to generate a random location from a predefined list
void get_random_location(char *location, int length) {
    const char *locations[] = {"San Francisco", "Los Angeles", "Tokyo", "New York", "Mexico City", "Istanbul", "London", "Sydney", "Beijing"};
    int index = rand() % 9;  // Random index from 0 to 8
    strncpy(location, locations[index], length - 1);
    location[length - 1] = '\0';
}

// Function to print seismic event details
void print_event(SeismicEvent *event) {
    printf("Magnitude: %.2f, Location: %s, Timestamp: %s", event->magnitude, event->location, ctime(&(event->timestamp)));
}

// Function to write all recorded events to a log file
void write_logs_to_file() {
    FILE *log_file = fopen(LOG_FILE, "w");
    if (log_file != NULL) {
        for (int i = 0; i < event_count; i++) {
            fprintf(log_file, "%.2f %s %ld\n", seismic_events[i].magnitude, seismic_events[i].location, seismic_events[i].timestamp);
        }
        fclose(log_file);
    }
}

// Function to read logged data from file (simulating historical data)
void read_logs_from_file() {
    FILE *log_file = fopen(LOG_FILE, "r");
    if (log_file != NULL) {
        float magnitude;
        char location[256];
        time_t timestamp;

        while (fscanf(log_file, "%f %s %ld\n", &magnitude, location, &timestamp) == 3) {
            seismic_events[event_count].magnitude = magnitude;
            strncpy(seismic_events[event_count].location, location, sizeof(seismic_events[event_count].location) - 1);
            seismic_events[event_count].timestamp = timestamp;
            event_count++;
        }
        fclose(log_file);
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_GPS_DATA_LEN 100
#define NMEA_SENTENCE_LEN 80

char gps_data[MAX_GPS_DATA_LEN];
char nmea_sentence[NMEA_SENTENCE_LEN];

typedef struct {
    float latitude;
    float longitude;
    float altitude;
    char time[11]; 
    char status;   
} GPS_Data;


void initGPSData(GPS_Data *gps);
bool parseNMEASentence(char *nmea, GPS_Data *gps);
void extractDataFromSentence(char *nmea, GPS_Data *gps);
void processGPSData(GPS_Data *gps);
void printGPSData(GPS_Data *gps);
void handleSerialInput(void);
void processData(char *data);
void initializeParser(void);
bool validateChecksum(char *nmea);
void processLongitude(char *longitude, char hemisphere, GPS_Data *gps);
void processLatitude(char *latitude, char hemisphere, GPS_Data *gps);
void extractTime(char *time_str, GPS_Data *gps);
void processAltitude(char *altitude_str, GPS_Data *gps);
void processStatus(char *status_str, GPS_Data *gps);
void storeNMEASentence(char *sentence);
void parseAdditionalFields(char *field_data, GPS_Data *gps);

int main(void) {
    while (1) {
        handleSerialInput();
    }
    return 0;
}

void handleSerialInput(void) {
    strcpy(gps_data, "$GPGGA,123456.789,3751.65,S,14504.00,E,1,08,1.0,10.0,M,0.0,M,,*47");
    printf("Received GPS Data: %s\n", gps_data);
    
    GPS_Data gps;
    initGPSData(&gps);

    if (parseNMEASentence(gps_data, &gps)) {
        processGPSData(&gps);
    } else {
        printf("Invalid NMEA sentence.\n");
    }
}

void initGPSData(GPS_Data *gps) {
    gps->latitude = 0.0f;
    gps->longitude = 0.0f;
    gps->altitude = 0.0f;
    memset(gps->time, 0, sizeof(gps->time));
    gps->status = 'V';
}

bool parseNMEASentence(char *nmea, GPS_Data *gps) {
    if (nmea == NULL) {
        return false;
    }
    if (strncmp(nmea, "$GPGGA", 6) == 0) {
        extractDataFromSentence(nmea, gps);
        return true;
    }
    return false;
}

void extractDataFromSentence(char *nmea, GPS_Data *gps) {
    char *token;
    int field_count = 0;
    token = strtok(nmea, ",");
    
    while (token != NULL) {
        field_count++;
        if (field_count == 2) {
            extractTime(token, gps);
        }
        if (field_count == 3) {
            processLatitude(token, 'N', gps);
        }
        if (field_count == 4) {
            processLatitude(token, 'S', gps);
        }
        if (field_count == 5) {
            processLongitude(token, 'E', gps);
        }
        if (field_count == 6) {
            processLongitude(token, 'W', gps);
        }
        if (field_count == 10) {
            processAltitude(token, gps);
        }
        if (field_count == 7) {
            processStatus(token, gps);
        }
        token = strtok(NULL, ",");
    }
}

void processLongitude(char *longitude, char hemisphere, GPS_Data *gps) {
    gps->longitude = atof(longitude);
    if (hemisphere == 'W') {
        gps->longitude = -gps->longitude;
    }
}

void processLatitude(char *latitude, char hemisphere, GPS_Data *gps) {
    gps->latitude = atof(latitude);
    if (hemisphere == 'S') {
        gps->latitude = -gps->latitude;
    }
}

void extractTime(char *time_str, GPS_Data *gps) {
    strncpy(gps->time, time_str, 10);
    gps->time[10] = '\0';
}

void processAltitude(char *altitude_str, GPS_Data *gps) {
    gps->altitude = atof(altitude_str);
}

void processStatus(char *status_str, GPS_Data *gps) {
    if (strcmp(status_str, "1") == 0) {
        gps->status = 'A';
    } else {
        gps->status = 'V';
    }
}

void processGPSData(GPS_Data *gps) {
    printGPSData(gps);
}

void printGPSData(GPS_Data *gps) {
    printf("GPS Data:\n");
    printf("Time: %s\n", gps->time);
    printf("Latitude: %.5f\n", gps->latitude);
    printf("Longitude: %.5f\n", gps->longitude);
    printf("Altitude: %.2f meters\n", gps->altitude);
    if (gps->status == 'A') {
        printf("Status: Active\n");
    } else {
        printf("Status: Void\n");
    }
}

void processData(char *data) {

}

void initializeParser(void) {
    
}

bool validateChecksum(char *nmea) {

    return true;
}

void storeNMEASentence(char *sentence) {
    
}

void parseAdditionalFields(char *field_data, GPS_Data *gps) {
    
}


void handleSerialInput2(void) {
    
    strcpy(gps_data, "$GPRMC,123456.789,A,3751.65,S,14504.00,E,1.0,10.0,M,0.0,M,,*47");
    printf("Received GPS Data: %s\n", gps_data);
    
    GPS_Data gps;
    initGPSData(&gps);

    if (parseNMEASentence(gps_data, &gps)) {
        processGPSData(&gps);
    } else {
        printf("Invalid NMEA sentence.\n");
    }
}

void initGPSData2(GPS_Data *gps) {
    gps->latitude = 0.0f;
    gps->longitude = 0.0f;
    gps->altitude = 0.0f;
    memset(gps->time, 0, sizeof(gps->time));
    gps->status = 'V';
}

void processLongitude2(char *longitude, char hemisphere, GPS_Data *gps) {
    gps->longitude = atof(longitude);
    if (hemisphere == 'W') {
        gps->longitude = -gps->longitude;
    }
}

void processLatitude2(char *latitude, char hemisphere, GPS_Data *gps) {
    gps->latitude = atof(latitude);
    if (hemisphere == 'S') {
        gps->latitude = -gps->latitude;
    }
}

void extractTime2(char *time_str, GPS_Data *gps) {
    strncpy(gps->time, time_str, 10);
    gps->time[10] = '\0';
}

void processAltitude2(char *altitude_str, GPS_Data *gps) {
    gps->altitude = atof(altitude_str);
}

void processStatus2(char *status_str, GPS_Data *gps) {
    if (strcmp(status_str, "1") == 0) {
        gps->status = 'A';
    } else {
        gps->status = 'V';
    }
}

void printGPSData2(GPS_Data *gps) {
    printf("GPS Data:\n");
    printf("Time: %s\n", gps->time);
    printf("Latitude: %.5f\n", gps->latitude);
    printf("Longitude: %.5f\n", gps->longitude);
    printf("Altitude: %.2f meters\n", gps->altitude);
    if (gps->status == 'A') {
        printf("Status: Active\n");
    } else {
        printf("Status: Void\n");
    }
}

void handleSerialInput3(void) {
    
    strcpy(gps_data, "$GPGGA,122233.789,3456.65,N,12345.00,E,1,08,1.0,20.0,M,0.0,M,,*47");
    printf("Received GPS Data: %s\n", gps_data);

    GPS_Data gps;
    initGPSData(&gps);

    if (parseNMEASentence(gps_data, &gps)) {
        processGPSData(&gps);
    } else {
        printf("Invalid NMEA sentence.\n");
    }
}

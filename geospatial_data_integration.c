#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EARTH_RADIUS 6371.0 

typedef struct {
    double latitude;
    double longitude;
    char name[50];
} GeoLocation;


double haversine(double lat1, double lon1, double lat2, double lon2) {
    double lat1Rad = lat1 * M_PI / 180.0;
    double lon1Rad = lon1 * M_PI / 180.0;
    double lat2Rad = lat2 * M_PI / 180.0;
    double lon2Rad = lon2 * M_PI / 180.0;

    double dLat = lat2Rad - lat1Rad;
    double dLon = lon2Rad - lon1Rad;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1Rad) * cos(lat2Rad) *
               sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS * c; 
}


void printGeoLocation(GeoLocation location) {
    printf("Location: %s\n", location.name);
    printf("Latitude: %.6f, Longitude: %.6f\n", location.latitude, location.longitude);
}


void storeLocations(GeoLocation *locations) {
   
    locations[0] = (GeoLocation){37.7749, -122.4194, "San Francisco"};
    locations[1] = (GeoLocation){34.0522, -118.2437, "Los Angeles"};
    locations[2] = (GeoLocation){40.7128, -74.0060, "New York"};
    locations[3] = (GeoLocation){51.5074, -0.1278, "London"};
    locations[4] = (GeoLocation){48.8566, 2.3522, "Paris"};
}


void displayLocations(GeoLocation *locations, int numLocations) {
    for (int i = 0; i < numLocations; i++) {
        printGeoLocation(locations[i]);
    }
}


GeoLocation findNearestLocation(GeoLocation *locations, int numLocations, GeoLocation refLocation) {
    double minDistance = -1;
    GeoLocation nearestLocation;
    for (int i = 0; i < numLocations; i++) {
        double distance = haversine(refLocation.latitude, refLocation.longitude, locations[i].latitude, locations[i].longitude);
        if (minDistance == -1 || distance < minDistance) {
            minDistance = distance;
            nearestLocation = locations[i];
        }
    }
    return nearestLocation;
}


void findLocationsInRadius(GeoLocation *locations, int numLocations, GeoLocation refLocation, double radius) {
    printf("Locations within %.2f km of %s:\n", radius, refLocation.name);
    for (int i = 0; i < numLocations; i++) {
        double distance = haversine(refLocation.latitude, refLocation.longitude, locations[i].latitude, locations[i].longitude);
        if (distance <= radius) {
            printGeoLocation(locations[i]);
        }
    }
}

void sortLocationsByDistance(GeoLocation *locations, int numLocations, GeoLocation refLocation) {
    double *distances = (double *)malloc(numLocations * sizeof(double));


    for (int i = 0; i < numLocations; i++) {
        distances[i] = haversine(refLocation.latitude, refLocation.longitude, locations[i].latitude, locations[i].longitude);
    }


    for (int i = 0; i < numLocations - 1; i++) {
        for (int j = i + 1; j < numLocations; j++) {
            if (distances[i] > distances[j]) {
                
                double tempDist = distances[i];
                distances[i] = distances[j];
                distances[j] = tempDist;

            
                GeoLocation tempLoc = locations[i];
                locations[i] = locations[j];
                locations[j] = tempLoc;
            }
        }
    }


    printf("\nLocations sorted by distance from %s:\n", refLocation.name);
    for (int i = 0; i < numLocations; i++) {
        printGeoLocation(locations[i]);
        printf("Distance: %.2f km\n", distances[i]);
    }

    free(distances);
}

void getUserLocationInput(GeoLocation *location) {
    printf("Enter the name of the location: ");
    scanf("%s", location->name);

    printf("Enter the latitude: ");
    scanf("%lf", &location->latitude);

    printf("Enter the longitude: ");
    scanf("%lf", &location->longitude);
}

int main() {
    GeoLocation locations[10]; 
    GeoLocation userLocation = {37.7749, -122.4194, "User's Location"};
    int numLocations = 5;

    storeLocations(locations);

    printf("\nWould you like to add a new location? (y/n): ");
    char userChoice;
    scanf(" %c", &userChoice);
    if (userChoice == 'y' || userChoice == 'Y') {
        GeoLocation newLocation;
        getUserLocationInput(&newLocation);
        locations[numLocations] = newLocation;
        numLocations++;
    }


    printf("\nAll Stored Locations:\n");
    displayLocations(locations, numLocations);

    GeoLocation nearest = findNearestLocation(locations, numLocations, userLocation);
    printf("\nThe nearest location to %s is:\n", userLocation.name);
    printGeoLocation(nearest);

    double distance = haversine(userLocation.latitude, userLocation.longitude, nearest.latitude, nearest.longitude);
    printf("\nDistance to nearest location: %.2f km\n", distance);

    findLocationsInRadius(locations, numLocations, userLocation, 500.0);

    sortLocationsByDistance(locations, numLocations, userLocation);

    return 0;
}

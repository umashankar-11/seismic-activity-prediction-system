# Seismic Activity Prediction

This project simulates seismic activity recording and prediction. It uses random seismic data generation to simulate real-world earthquake occurrences, logs the data to a file, and makes a basic prediction about the likelihood of a strong earthquake based on recent activity. The prediction is based on seismic events with magnitudes above a certain threshold within a given time window.

## Features

- **Seismic Event Simulation**: Randomly generates seismic event data, including magnitude and location.
- **Event Logging**: Seismic events are logged to a file (`seismic_events.txt`) for future reference.
- **Seismic Activity Analysis**: Analyzes the historical seismic activity to calculate statistics such as:
  - Total number of events
  - Number of events with magnitudes above a specified threshold
  - Percentage of strong seismic events
- **Earthquake Prediction**: Predicts the likelihood of a strong earthquake occurring in the near future based on recent seismic events.
- **Data Persistence**: Logs seismic events to a file, and reads from the file to simulate historical data on program startup.

## Prerequisites

To compile and run this project, you need a C/C++ development environment. You will also need the following libraries:

- **Standard C Library** (for time manipulation, string handling, and file I/O)
- **Math Library** (for generating random seismic magnitudes)

## Compilation & Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/umashankar-11//seismic-activity-prediction-system-using-c-language.git
   cd seismic-activity-prediction-system-using-c-language
   ```

2. Compile the code using a C/C++ compiler (such as `gcc` or `g++`):
   ```bash
   gcc -o earthquake.c
   ```

3. Run the executable:
   ```bash
   .//seismic-activity-prediction-system-using-c-language
   ```

## How It Works

1. **Data Generation**: The program simulates the occurrence of seismic events by generating random magnitudes (between 4.0 and 9.0) and selecting random locations from a predefined list.
   
2. **Logging Events**: Each seismic event is logged to a file (`seismic_events.txt`) for record-keeping. This includes the magnitude, location, and timestamp of each event.

3. **Analysis**: After generating a set of events, the program analyzes the recorded seismic data:
   - Counts the total number of events
   - Identifies the number of high-magnitude events (those greater than or equal to the defined `MAGNITUDE_THRESHOLD`)

4. **Prediction**: Based on the recent seismic activity, the program predicts whether a strong earthquake is likely in the near future:
   - The program considers events from the last `PREDICTION_WINDOW` days.
   - If more than half of the recent events are high-magnitude, a prediction is made that a strong earthquake is likely.

## Configuration

- **MAGNITUDE_THRESHOLD**: Minimum magnitude (in Richter scale) for an event to be considered a "strong" earthquake. Default is `5.0`.
- **PREDICTION_WINDOW**: Number of days to look back for predicting future seismic activity. Default is `7` days.
- **MAX_EVENTS**: The maximum number of seismic events that can be recorded. Default is `10000`.
- **LOG_FILE**: The file where seismic events are logged. Default is `seismic_events.txt`.

## Example Output

### Seismic Activity Analysis:
```
--- Seismic Activity Analysis ---
Total Events: 100
High Magnitude Events (>= 5.0): 35
Percentage of High Magnitude Events: 35.00%
```

### Earthquake Prediction:
```
--- Earthquake Prediction ---
Recent Events within the last 7 days: 30
High Magnitude Events: 15
Prediction: A strong earthquake is more likely in the coming days!
```

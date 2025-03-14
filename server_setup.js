const express = require('express');
const axios = require('axios');
const mongoose = require('mongoose');
require('dotenv').config();

const Prediction = require('./models/Prediction');
const UserAlert = require('./models/UserAlert');

const app = express();
const PORT = process.env.PORT || 5000;

mongoose.connect(process.env.MONGO_URI, {
  useNewUrlParser: true,
  useUnifiedTopology: true,
})
  .then(() => console.log("MongoDB connected"))
  .catch((err) => console.log(err));

app.use(express.json());


app.get('/api/recent-quakes', async (req, res) => {
  try {
    const response = await axios.get('https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/all_hour.geojson');
    res.json(response.data);
  } catch (error) {
    console.error(error);
    res.status(500).json({ message: 'Error fetching seismic data' });
  }
});


app.post('/api/predict', async (req, res) => {
  const { location } = req.body;

  const prediction = new Prediction({
    location,
    risk: "Medium",  
    predictionTime: new Date().toLocaleString(),
  });

  try {
    await prediction.save();
    res.json(prediction);
  } catch (error) {
    res.status(500).json({ message: 'Error saving prediction' });
  }
});

app.post('/api/subscribe-alert', async (req, res) => {
  const { email, location, alertLevel } = req.body;

  const userAlert = new UserAlert({ email, location, alertLevel });

  try {
    await userAlert.save();
    res.status(201).json({ message: 'Alert subscription successful!' });
  } catch (error) {
    res.status(500).json({ message: 'Error subscribing to alerts' });
  }
});

app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});

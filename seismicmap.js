import React, { useEffect, useState } from 'react';
import { MapContainer, TileLayer, Marker, Popup } from 'react-leaflet';
import L from 'leaflet';

function SeismicMap() {
  const [quakes, setQuakes] = useState([]);

  useEffect(() => {
    
    const fetchData = async () => {
      const response = await fetch('https://earthquake.usgs.gov/earthquakes/feed/v1.0/summary/all_hour.geojson');
      const data = await response.json();
      setQuakes(data.features);
    };
    
    fetchData();
  }, []);

  return (
    <MapContainer center={[37.7749, -122.4194]} zoom={5} style={{ height: "400px", width: "100%" }}>
      <TileLayer
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
      />
      {quakes.map((quake, index) => {
        const { coordinates } = quake.geometry;
        const [longitude, latitude] = coordinates;
        const magnitude = quake.properties.mag;
        
        return (
          <Marker key={index} position={[latitude, longitude]}>
            <Popup>
              <div>
                <h3>Magnitude: {magnitude}</h3>
                <p>Location: {quake.properties.place}</p>
                <p>Time: {new Date(quake.properties.time).toLocaleString()}</p>
              </div>
            </Popup>
          </Marker>
        );
      })}
    </MapContainer>
  );
}

export default SeismicMap;

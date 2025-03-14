import React, { useEffect, useState } from 'react';

function RecentQuakes() {
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
    <div>
      <h2>Recent Earthquakes</h2>
      <ul>
        {quakes.map((quake, index) => (
          <li key={index}>
            <strong>{quake.properties.place}</strong> - Magnitude: {quake.properties.mag}
            <br />
            {new Date(quake.properties.time).toLocaleString()}
          </li>
        ))}
      </ul>
    </div>
  );
}

export default RecentQuakes;

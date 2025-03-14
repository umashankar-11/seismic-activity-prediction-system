import React, { useState } from 'react';

function PredictionForm() {
  const [location, setLocation] = useState('');

  const handleSubmit = (e) => {
    e.preventDefault();
    
    alert(`Seismic prediction for ${location} is being processed!`);
  };

  return (
    <form onSubmit={handleSubmit}>
      <input 
        type="text" 
        value={location} 
        onChange={(e) => setLocation(e.target.value)} 
        placeholder="Enter location" 
        required 
      />
      <button type="submit">Get Prediction</button>
    </form>
  );
}

export default PredictionForm;

import React from 'react';
import { Line } from 'react-chartjs-2';
import { Chart as ChartJS, Title, Tooltip, LineElement, CategoryScale, LinearScale } from 'chart.js';

ChartJS.register(Title, Tooltip, LineElement, CategoryScale, LinearScale);

function SeismicChart({ data }) {
  const chartData = {
    labels: data.map(item => item.time),
    datasets: [
      {
        label: 'Seismic Activity',
        data: data.map(item => item.magnitude),
        borderColor: 'rgba(75,192,192,1)',
        borderWidth: 1,
        fill: false,
      },
    ],
  };

  return <Line data={chartData} />;
}

export default SeismicChart;

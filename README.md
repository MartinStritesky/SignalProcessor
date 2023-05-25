# Signal Processor
Demonstration of signal digitalization!

This app is built to demonstrate quantization and sampling of analog signal by using QT framework.
- two QCustomPlot widgets are used for plotting of scatter points and functions - original and digitized signals
- Spline interpolation library

The user can select between 3 analog signal representations
- Sine function
- Wavelet function
- Square wave function

Input signal frequency can be adjusted by a slider. 

Once analog signal is defined the user can adjust the sampling frequency. Sampling frequency is visualized by scatter plot that can be toggled ON/OFF. Quantization in optional feature enabled by checking the checkbox and selecting type of A/D converter (number of available bits). If checked, the program adjusts levels o each point to relevant quantization level.

Reconstruction of digitized signal is done by intepolation with Cubic spline. Reconstructed signal is visualized and the original vs sampling frequency ratio is visible in the app. This demonstrates Nyquist-Shannon sampling theorem - ratios above 2 start to give precise reconstruction of analog signal. 


![Screenshot from 2023-05-08 21-06-40](https://user-images.githubusercontent.com/113254850/236910735-d56d27ed-f92a-4225-8ace-ab368565c6e5.png)

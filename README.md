# 2D Fourier series visualisation

If we have a 2D array y(n,m), (maybe from sampling a 2D function f(x,y), periodic in N in both variables (y(n+N,m) = y(n,m), y(n,m + N) = y(n,m)) then that array can be matched by a 2D fourier series of N^2 members. Where each member is a sinusoid dependend on both both coordinates.

The following formulas were used (derived by analogy from the 1D Fourier series):

![Alt text](/../screenshots/img/formula.png?raw=true "Optional Title")

Formula 2 is used to calculate the coefficients based on the values of the sample points. Formula 1 gives the same values as the starting array y(n,m), but because it is a sum of continuous functions, we can also interpolate the values between sample points and achieve smooth results.

![Alt text](/../screenshots/img/screen.jpg?raw=true "Optional Title")

The visualisation allows one to pick a grid size (NxN), and change values of sample points. Every change of values will calculate the Fourier coefficients (formula 2) again and will yield a new interpolation.

The values of the sample points can be changed in real time, as well as panning, zooming, rotating the mesh, but the size of the grid and amount of detail of the surface must be changed in the global.h file and the aplication recompiled.

The mathematical details (actualy calculating the complex coefficients and converting the complex valued sum into real values, etc) are in DiscreteFourier2D.cpp.




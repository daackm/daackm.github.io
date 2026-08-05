//Processing CoilCar 8/5/2026 9:45:22 AM
//SCAD File Name: C:\Users\Ackmann Family\source\repos\Coil Car\CoilCar_Coil.SCAD
//
//Software Version 0.01  06FEB26
//
//Coil Style = Coil
//This OpenSCAD code was created by Perry_1 And discovered on a Yahoo search.
//Dave Ackmann modified the code to replace the hard coded value of 90
//inside the polygon computation
//with a constant "density" equal to 270 which, as it increases, will
//results in a more tightly wound coil.
r = 1;
thickness = 1;
loops = 7.5;
density = 270;
coilheight = 25;
linear_extrude(height = coilheight)
        polygon(points = concat( [for(t=[density:360*loops])
[(r-thickness+t/density)*sin(t),
(r-thickness+t/density)*cos(t)]],
[for(t= [360*loops:-1:density])
[(r+t/density)*sin(t),
(r+t/density)*cos(t)]]));

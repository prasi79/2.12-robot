clear d;
d = DynamixelConn(7, 4);
rail = Rail(d);

% call rail.setOrigin() when the sifter is at the bottom

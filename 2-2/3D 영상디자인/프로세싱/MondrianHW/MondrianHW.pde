size(900,900);
background(246, 250, 251);

strokeWeight(16); //red rec
fill(255,10,44);
rect(0, 80, 350, 230);

strokeWeight(16); //red yellow Vertical line
line(351, 0, 353, 900);

strokeWeight(30);
stroke(0);  //first line
line(80, 0, 90, 900);

//black rec
fill(0);
rect(100, 770, 700, 130);

strokeWeight(20);
fill(255,232,0);  //yellow rec
rect(0, 700, 350, 230);

noFill(); // white rec
strokeWeight(18);
rect(353, 210, 325, 290);

//blue rec
strokeWeight(18);
fill(61, 48, 104);
rect(678, 500, 220, 300);


//Black Horizontal Line (for storkeWeight)
strokeWeight(20);
line(0, 318, 350, 318);

line(0, 695, 350, 695);


//WhiteTri
noStroke();  //UL tri
fill(255);
triangle(0,0, 450,0, 0,450);

noStroke();  //DL tri
fill(255);
triangle(0, 900, 450, 900, 0, 450);

noStroke();  //UpRight tri
fill(255);
triangle(900, 0, 450, 0, 900, 450);

noStroke();  //DownRight tri
fill(255);
triangle(900, 900, 450, 900, 900, 450);

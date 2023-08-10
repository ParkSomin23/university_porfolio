import processing.video.*;
Movie myMovie;
PImage pre;

int count = 0;

void setup()
{
  size(1280, 772,P3D);
  background(0);

  myMovie = new Movie(this, "t.mp4");
  myMovie.play();

  pre = loadImage("prePic5.tif");
  
 
}

void draw()
{
  image(myMovie, 0, 0);

  if (myMovie.time() == 0.000)
    play();

  //play_bar
  float play_x = map(myMovie.time(), 0, myMovie.duration(), 0, 1280);

  strokeWeight(8);
  stroke(200, 10);
  line(0, 724, width, 724);
  stroke(196, 48, 43);
  line(0, 724, play_x, 724);

  mouseMoved();

  int min = int(myMovie.time())/60;
  int sec = int(myMovie.time()) - 60*min;

  fill(0);
  noStroke();
  rect(45,730, 180, 40);
  fill(255);
  textAlign(LEFT,CENTER);
  textSize(24);
  text("0"+min+":"+sec+"/02:52", 45, 750 );
 
  if (myMovie.time() == myMovie.duration())
  {
    replay();
  }
}

int move = 3;

void mouseMoved()
{
  //mouse-time
  float pre_time = map(mouseX, 0, 1280, 0, myMovie.duration()-6);
  int tim = int(map(mouseX, 0, 1280, 0, myMovie.duration()));

  if (mouseY < 733 && mouseY > 718)
  { 
    PImage cut;

    int y = int(pre_time/6) * 36;
    int x = int((pre_time - 6*y/36)/0.2) * 64;

    cut = pre.get(x, y, 64, 36);


    int min = tim/60;
    tim = tim - min*60;


    if (pre_time >= 148.6)
    {
      fill(0);
      noStroke();
      rect(1139, 620, 128, 20);
      fill(255);
      textAlign(LEFT);
      textSize(15);
      text("0"+min +":"+tim, 1139+45, 635);
      image(cut, 1139, 640, 128, 72);
    } else
    { 
      fill(0);
      noStroke();
      rect(mouseX, 620, 128, 20);
      fill(255);
      textAlign(LEFT);
      textSize(15);
      text("0"+min+":"+tim, mouseX+45, 635);
      image(cut, mouseX, 640, 128, 72);
    }
    println(pre_time +"  " +mouseX);
  }
}

void pause()
{   
  noStroke();
  fill(0);
  rect(0+move, 730, 37+move, 40);
  fill(255);
  triangle(5+move, 736, 5+move, 764, 30+move, 750);

  myMovie.pause();
}

void play()
{
  myMovie.play();

  noStroke();
  fill(0);
  rect(0+move, 730, 37+move, 40);
  strokeWeight(10);
  stroke(255);
  strokeCap(SQUARE);
  line(9+move, 736, 9+move, 764);
  line(22+move, 736, 22+move, 764);
}

void replay()
{
  fill(200, 30);
  rect(565, 285, 150, 150);
  strokeWeight(10);
  noFill();
  stroke(255);
  arc(640, 360, 100, 100, PI*0.2, 1.95*PI);

  fill(255);
  strokeWeight(2);
  triangle(672, 342, 700, 338, 689, 363);
}

void mouseClicked()
{
  //pause&play
  if (mouseX < 40+move && mouseY >728)
  {
    if (count % 2 == 0)
      pause();     
    else
      play();

    count++;
  }

  //move to
  float preX = map(mouseX, 0, 1280, 0, myMovie.duration());
  if (mouseY<733 && mouseY>718)
  {
    myMovie.jump(preX);
  }

  //again
  if (myMovie.time() == myMovie.duration())
  {
    if (mouseX>565 && mouseX<715 && mouseY > 285 && mouseY < 435)
      myMovie.jump(0);
  }
}

void movieEvent(Movie m)
{
  m.read();
}

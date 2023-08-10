import fisica.*;

import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.spi.*;

Minim minim;
AudioPlayer player;
FFT fft;

PImage cloud, desert;

FWorld world;
FCircle[] star;
FCircle[] fa;
FDistanceJoint[] dJoint;
FCircle sun;

int loopSize;
float angle;

color[] starCol = {color(155, 176, 255), color(170, 191, 255), color(202, 215, 255), 
  color(248, 247, 255), /*color(239,239,232),*/ color(255, 244, 234), 
  color(255, 210, 161), color(255, 204, 111)};

void setup()
{

  size(1920, 1080, P3D);

  minim = new Minim(this);
  player = minim.loadFile("Unity+-+Drop.mp3");
  player.play();

  cloud = loadImage("s3.jpg"); 
  desert = loadImage("city3.png");

  fft = new FFT(player.bufferSize(), player.sampleRate());

  Fisica.init(this);
  world = new FWorld();
  world.setGravity(0, 0);

  loopSize = fft.specSize()/6;

  sun = new FCircle(0.1);
  sun.setFill(0, 0);
  sun.setNoStroke();
  sun.setPosition(width/2, height/3+150);
  sun.setStatic(true);
  world.add(sun);

  star = new FCircle[loopSize];
  dJoint = new FDistanceJoint[loopSize];
  float[] len = new float[loopSize+1];
  len[0] = 0;


  for (int i = 0; i<loopSize; i++)
  {
    star[i] = new FCircle(random(1, 2));
    star[i].setPosition(random(width), random(height));
    star[i].setFillColor(starCol[int(i/12)%7]);
    star[i].setNoStroke();
    star[i].setDamping(0.2);

    dJoint[i] = new FDistanceJoint(sun, star[i]);
    dJoint[i].calculateLength();

    //dJoint[i].setLength(random(30)*i);
    dJoint[i].setLength(len[i]+random(23));
    len[i+1] = len[i]+random(23);

    dJoint[i].setDrawable(false);
    dJoint[i].setNoStroke();
    dJoint[i].getReactionTorque();

    world.add(star[i]);
    world.add(dJoint[i]);
  }

  image(cloud, 0, 0, 1920, 1280);
  println(loopSize/7);
  println(int(0/(loopSize/12))%7);
}

void draw()
{
  if (frameCount ==1)
    image(cloud, 0, 0, 1920, 1280);
  fft.forward(player.mix);

  angle -= PI/360;

  for (int i = 0; i<loopSize; i++)
  {
    float magnitude = fft.getBand(loopSize-i)*4;
    star[i].setVelocity(magnitude*cos(angle), magnitude*sin(angle));
    //star[i].setFill(10*fft.getBand(i));
    star[i].setDensity(100*fft.getBand(loopSize-i));
  }


  world.step(1);
  world.draw();

  image(desert, 0, 525);

  for (int i = 0; i<loopSize; i++)
  {
    strokeWeight(1);
    stroke(starCol[6-(i/12)%7]);
    line(12*i, height, 12*i, height-3*fft.getBand(i));
    line(width-12*i, height, width-12*i, height-3*fft.getBand(i));
  }

  if (mousePressed)
  {
    //image(cloud, 0, 0, 1920, 1280);
    sun.setPosition(mouseX, mouseY);
  }
  if (player.isPlaying() == false)
    saveFrame("screenshot.png");
}

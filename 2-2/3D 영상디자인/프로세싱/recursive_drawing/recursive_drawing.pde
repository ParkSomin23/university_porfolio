import processing.pdf.*;

void setup()
{
  size(1700, 1200, PDF, "20173994_SominPark.pdf");
  background(255);
  
  rec_uni(0, 0, width, height);
  rec_curve(width-500, height);
}

void rec_uni(float x1, float y1, float x2, float y2)
{
  float halfX = (x2-x1)/2;
  float halfY = (y2-y1)/2;

  if (halfX < 10)
    return;
  else
  {
    noStroke();
    fill(HSB, 10, random(100), random(100));
    rect(x1, y1, halfX, halfY);
    
    strokeWeight(random(1,5));
    stroke(random(255));
    noFill();
    rect(x1, y1, random(0.8,1.2)*halfX/2, random(0.8,1.2)*halfX/2);
    
    strokeWeight(random(0,2));
    ellipse(x1+halfY, y1+halfX, halfX, halfX);
  }
  
  rec_uni(x1, y1+halfY, x1+halfX, y2);
  rec_uni(x1, y1, x1+halfX, y1+halfY);
  rec_uni(x1+halfX, y1+halfY, x2, y2);
  rec_uni(x1+halfX, y1, x2, y1+halfY);
}


void rec_curve(int x, int y)
{
  if (x==0) {
    return;
  } else
  {
    stroke(random(0, 255));
    strokeWeight(1);
    line(0, y-10, x-10, height);
    line(x-10+500, 0, width, y-10);
    line(0, y-10, abs(width-500-x), 0);
    line(abs(width-x), height, width, y-10);
    rec_curve(x-10, y-10);
  }
 
}

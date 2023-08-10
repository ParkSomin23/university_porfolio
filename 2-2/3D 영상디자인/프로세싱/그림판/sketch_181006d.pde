import controlP5.*;
ControlP5 cp5;
Accordion accordion;

color c = color(255);

void setup()
{
  size(1800, 900); //200 is for tools
  background(255);
  gui();
}

void draw()
{  
  noStroke();
  fill(150);
  rect(0, 0, 200, height);


  stroke(c);

  float stroke_Weight = cp5.getController("Stroke").getValue();
  strokeWeight(stroke_Weight);

  if (mousePressed==true) {
    line(mouseX, mouseY, pmouseX, pmouseY);
  }
}

void gui()
{
  cp5 = new ControlP5(this);

  //Stroke Weight
  cp5.addSlider("Stroke")
    .setPosition(40, 40)
    .setSize(100, 20)
    .setRange(1, 50)
    .setValue(10)
    .setColorCaptionLabel(255)
    ;

  //Eraser
  cp5.addButton("Eraser")
    .setPosition(40, 80)
    .setSize(100, 20)
    .setValue(color(255))
    ;

  //Save
  cp5.addButton("SAVE")
    .setPosition(10, 800)
    .setSize(180, 80)
    ;

  //Grey
  Group grey = cp5.addGroup("B/G/W")
    .setBackgroundColor(color(0, 64))
    .setWidth(180)
    ;

  cp5.addSlider("Grey")
    .setPosition(30, 15)
    .setSize(100, 20)
    .setRange(0, 255)
    .setValue(150)
    .moveTo(grey)
    ;

  cp5.addButton("Black")
    .setPosition(30, 50)
    .setSize(50, 20)
    .setValue(0)
    .moveTo(grey)
    ;

  cp5.addButton("White")
    .setPosition(80, 50)
    .setSize(50, 20)
    .setValue(255)
    .moveTo(grey)
    ;

  //Basic Color
  Group basic_color = cp5.addGroup("Basic Color Selection")
    .setBackgroundColor(color(0, 64))
    .setBackgroundHeight(60)
    .setWidth(180)
    .setPosition(10, 380)
    ;


  //Color Selection
  Group color_select = cp5.addGroup("Color Selection")
    .setBackgroundColor(color(0, 64))
    .setBackgroundHeight(230)
    .setWidth(180)
    .setPosition(10, 140)
    ;

  //Accordion
  accordion = cp5.addAccordion("acc")
    .setPosition(10, 140)
    .setWidth(180)
    .addItem(color_select)
    .addItem(basic_color)
    .addItem(grey)
    ;

  accordion.open(0, 1, 2);
  accordion.setCollapseMode(Accordion.MULTI);

  PImage[] imgs_1= {loadImage("color_02.jpg"), loadImage("color_21.jpg"), loadImage("color_40.jpg")};

  cp5.addButton("color_01")
    .setPosition(6, 8)
    .setImages(imgs_1)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_2= {loadImage("color_03.jpg"), loadImage("color_22.jpg"), loadImage("color_41.jpg")};

  cp5.addButton("color_02")
    .setPosition(40, 8)
    .setImages(imgs_2)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_3= {loadImage("color_04.jpg"), loadImage("color_23.jpg"), loadImage("color_42.jpg")};

  cp5.addButton("color_03")
    .setPosition(73, 8) //+34
    .setImages(imgs_3)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_4= {loadImage("color_05.jpg"), loadImage("color_24.jpg"), loadImage("color_43.jpg")};

  cp5.addButton("color_04")
    .setPosition(107, 8) //+34
    .setImages(imgs_4)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_5= {loadImage("color_06.jpg"), loadImage("color_25.jpg"), loadImage("color_44.jpg")};

  cp5.addButton("color_05")
    .setPosition(141, 8) //+34
    .setImages(imgs_5)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_6= {loadImage("color_07.jpg"), loadImage("color_26.jpg"), loadImage("color_45.jpg")};

  cp5.addButton("color_06")
    .setPosition(6, 34) //+34/26
    .setImages(imgs_6)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_7= {loadImage("color_08.jpg"), loadImage("color_27.jpg"), loadImage("color_46.jpg")};

  cp5.addButton("color_07")
    .setPosition(39, 34) //+34
    .setImages(imgs_7)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_8= {loadImage("color_09.jpg"), loadImage("color_28.jpg"), loadImage("color_47.jpg")};

  cp5.addButton("color_08")
    .setPosition(73, 34) //+34
    .setImages(imgs_8)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_9= {loadImage("color_10.jpg"), loadImage("color_29.jpg"), loadImage("color_48.jpg")};

  cp5.addButton("color_09")
    .setPosition(106, 34) //+34
    .setImages(imgs_9)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_10= {loadImage("color_11.jpg"), loadImage("color_30.jpg"), loadImage("color_49.jpg")};

  cp5.addButton("color_10")
    .setPosition(140, 34) //+34
    .setImages(imgs_10)
    .updateSize()
    .moveTo(color_select)
    ;


  PImage[] imgs_11= {loadImage("color_12.jpg"), loadImage("color_31.jpg"), loadImage("color_50.jpg")};

  cp5.addButton("color_11")
    .setPosition(6, 60) //+34
    .setImages(imgs_11)
    .updateSize()
    .moveTo(color_select)
    ;


  PImage[] imgs_12= {loadImage("color_13.jpg"), loadImage("color_32.jpg"), loadImage("color_51.jpg")};

  cp5.addButton("color_12")
    .setPosition(40, 60) //+34
    .setImages(imgs_12)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_13= {loadImage("color_14.jpg"), loadImage("color_33.jpg"), loadImage("color_52.jpg")};

  cp5.addButton("color_13")
    .setPosition(73, 60) //+34
    .setImages(imgs_13)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_14= {loadImage("color_15.jpg"), loadImage("color_34.jpg"), loadImage("color_53.jpg")};

  cp5.addButton("color_14")
    .setPosition(107, 60) //+34
    .setImages(imgs_14)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_15= {loadImage("color_16.jpg"), loadImage("color_35.jpg"), loadImage("color_54.jpg")};

  cp5.addButton("color_15")
    .setPosition(141, 60) //+34
    .setImages(imgs_15)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_16= {loadImage("color_17.jpg"), loadImage("color_36.jpg"), loadImage("color_55.jpg")};

  cp5.addButton("color_16")
    .setPosition(6, 86) //+34
    .setImages(imgs_16)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_17= {loadImage("color_18.jpg"), loadImage("color_37.jpg"), loadImage("color_56.jpg")};

  cp5.addButton("color_17")
    .setPosition(40, 86) //+34
    .setImages(imgs_17)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_18= {loadImage("color_19.jpg"), loadImage("color_38.jpg"), loadImage("color_57.jpg")};

  cp5.addButton("color_18")
    .setPosition(73, 86) //+34
    .setImages(imgs_18)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_19= {loadImage("color_20.jpg"), loadImage("color_39.jpg"), loadImage("color_58.jpg")};

  cp5.addButton("color_19")
    .setPosition(107, 86) //+34
    .setImages(imgs_19)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_21 = {loadImage("color_97.jpg"), loadImage("color_116.jpg"), loadImage("color_135.jpg")};

  cp5.addButton("color_21")
    .setPosition(6, 118) //+34
    .setImages(imgs_21)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_22 = {loadImage("color_98.jpg"), loadImage("color_117.jpg"), loadImage("color_136.jpg")};

  cp5.addButton("color_22")
    .setPosition(40, 118) //+34
    .setImages(imgs_22)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_23 = {loadImage("color_99.jpg"), loadImage("color_117.jpg"), loadImage("color_136.jpg")};

  cp5.addButton("color_23")
    .setPosition(73, 118) //+34
    .setImages(imgs_23)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_24 = {loadImage("color_100.jpg"), loadImage("color_118.jpg"), loadImage("color_136.jpg")};

  cp5.addButton("color_24")
    .setPosition(107, 118) //+34
    .setImages(imgs_24)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_25 = {loadImage("color_101.jpg"), loadImage("color_119.jpg"), loadImage("color_137.jpg")};

  cp5.addButton("color_25")
    .setPosition(141, 118) //+34
    .setImages(imgs_25)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_26 = {loadImage("color_102.jpg"), loadImage("color_120.jpg"), loadImage("color_138.jpg")};

  cp5.addButton("color_26")
    .setPosition(6, 144) //+34
    .setImages(imgs_26)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_27 = {loadImage("color_103.jpg"), loadImage("color_121.jpg"), loadImage("color_139.jpg")};

  cp5.addButton("color_27")
    .setPosition(40, 144) //+34
    .setImages(imgs_27)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_28 = {loadImage("color_104.jpg"), loadImage("color_122.jpg"), loadImage("color_140.jpg")};

  cp5.addButton("color_28")
    .setPosition(74, 144) //+34
    .setImages(imgs_28)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_29 = {loadImage("color_105.jpg"), loadImage("color_123.jpg"), loadImage("color_141.jpg")};

  cp5.addButton("color_29")
    .setPosition(107, 144) //+34
    .setImages(imgs_29)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_30 = {loadImage("color_106.jpg"), loadImage("color_124.jpg"), loadImage("color_142.jpg")};

  cp5.addButton("color_30")
    .setPosition(141, 144) //+34
    .setImages(imgs_30)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_31 = {loadImage("color_107.jpg"), loadImage("color_125.jpg"), loadImage("color_143.jpg")};

  cp5.addButton("color_31")
    .setPosition(6, 170) //+34
    .setImages(imgs_31)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_32 = {loadImage("color_108.jpg"), loadImage("color_126.jpg"), loadImage("color_144.jpg")};

  cp5.addButton("color_32")
    .setPosition(41, 170) //+34
    .setImages(imgs_32)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_33 = {loadImage("color_109.jpg"), loadImage("color_127.jpg"), loadImage("color_145.jpg")};

  cp5.addButton("color_33")
    .setPosition(74, 170) //+34
    .setImages(imgs_33)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_34 = {loadImage("color_110.jpg"), loadImage("color_128.jpg"), loadImage("color_146.jpg")};

  cp5.addButton("color_34")
    .setPosition(107, 170) //+34
    .setImages(imgs_34)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_35 = {loadImage("color_111.jpg"), loadImage("color_129.jpg"), loadImage("color_147.jpg")};

  cp5.addButton("color_35")
    .setPosition(140, 170) //+34
    .setImages(imgs_35)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_36 = {loadImage("color_112.jpg"), loadImage("color_130.jpg"), loadImage("color_148.jpg")};

  cp5.addButton("color_36")
    .setPosition(6, 196) //+34
    .setImages(imgs_36)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_37 = {loadImage("color_113.jpg"), loadImage("color_131.jpg"), loadImage("color_149.jpg")};

  cp5.addButton("color_37")
    .setPosition(40, 196) //+34
    .setImages(imgs_37)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_38 = {loadImage("color_114.jpg"), loadImage("color_132.jpg"), loadImage("color_150.jpg")};

  cp5.addButton("color_38")
    .setPosition(74, 196) //+34
    .setImages(imgs_38)
    .updateSize()
    .moveTo(color_select)
    ;

  PImage[] imgs_39 = {loadImage("color_115.jpg"), loadImage("color_133.jpg"), loadImage("color_151.jpg")};

  cp5.addButton("color_39")
    .setPosition(107, 196) //+34
    .setImages(imgs_39)
    .updateSize()
    .moveTo(color_select)
    ;


  PImage[] basic_1= {loadImage("red_1.png"), loadImage("red_2.png"), loadImage("red_3.png")};

  cp5.addButton("basic_01")
    .setPosition(6, 8)
    .setImages(basic_1)
    .updateSize()
    .moveTo(basic_color)
    ;

  PImage[] basic_2= {loadImage("green_1.png"), loadImage("green_2.png"), loadImage("green_3.png")};

  cp5.addButton("basic_02")
    .setPosition(50, 8)
    .setImages(basic_2)
    .updateSize()
    .moveTo(basic_color)
    ;

  PImage[] basic_3= {loadImage("blue_1.png"), loadImage("blue_2.png"), loadImage("blue_3.png")};

  cp5.addButton("basic_03")
    .setPosition(94, 8)
    .setImages(basic_3)
    .updateSize()
    .moveTo(basic_color)
    ;

  PImage[] basic_4= {loadImage("magenta_1.png"), loadImage("magenta_2.png"), loadImage("magenta_3.png")};

  cp5.addButton("basic_04")
    .setPosition(6, 40)
    .setImages(basic_4)
    .updateSize()
    .moveTo(basic_color)
    ;

  PImage[] basic_5= {loadImage("yellow_1.png"), loadImage("yellow_2.png"), loadImage("yellow_3.png")};

  cp5.addButton("basic_05")
    .setPosition(50, 40)
    .setImages(basic_5)
    .updateSize()
    .moveTo(basic_color)
    ;

  PImage[] basic_6= {loadImage("cyan_1.png"), loadImage("cyan_2.png"), loadImage("cyan_3.png")};

  cp5.addButton("basic_06")
    .setPosition(94, 40)
    .setImages(basic_6)
    .updateSize()
    .moveTo(basic_color)
    ;
}


//Erase
public void Eraser(int theValue)
{
  c = theValue;
}


//SAVE
public void SAVE()
{
  fill(255);
  noStroke();
  rect(0, 0, 200, height);
  save("pic.jpg");
}

public void Grey(int theValue)
{
  c=color(theValue);
}

public void Black(int theValue)
{
  c=color(theValue);
}

public void White(int theValue)
{
  c=color(theValue);
}

//color
public void color_01() {
  c = color(255, 0, 0);
}

public void color_02() {
  c = color(241, 32, 1);
}

public void color_03() {
  c = color(241, 75, 1);
}

public void color_04() {
  c = color(234, 99, 0);
}

public void color_05() { 
  c = color(245, 134, 1);
}

public void color_06() {
  c = color(246, 173, 3);
}

public void color_07() {
  c = color(186, 208, 3);
}

public void color_08() {
  c = color(138, 188, 1);
}

public void color_09() {
  c = color(79, 170, 4);
}

public void color_10() { 
  c = color(2, 129, 0);
}

public void color_11() {
  c = color(1, 89, 75);
}

public void color_12() {
  c = color(3, 75, 100);
}

public void color_13() {
  c = color(1, 50, 117);
}

public void color_14() {
  c = color(41, 0, 118);
}

public void color_15() { 
  c = color(70, 0, 112);
}

public void color_16() {
  c = color(106, 1, 106);
}

public void color_17() {
  c = color(158, 0, 87);
}

public void color_18() {
  c = color(173, 0, 66);
}

public void color_19() {
  c = color(191, 0, 54);
}

public void color_21() {
  c = color(248, 126, 125);
}

public void color_22() {
  c = color(247, 143, 130);
}

public void color_23() {
  c = color(246, 167, 128);
}

public void color_24() {
  c = color(249, 178, 126);
}

public void color_25() { 
  c = color(248, 194, 124);
}

public void color_26() {
  c = color(251, 215, 129);
}

public void color_27() {
  c = color(222, 230, 129);
}

public void color_28() {
  c = color(197, 221, 127);
}

public void color_29() {
  c = color(167, 213, 125);
}

public void color_30() { 
  c = color(128, 190, 127);
}

public void color_31() {
  c = color(126, 171, 168);
}

public void color_32() {
  c = color(129, 162, 177);
}

public void color_33() {
  c = color(127, 151, 185);
}

public void color_34() {
  c = color(149, 128, 185);
}

public void color_35() { 
  c = color(164, 126, 183);
}

public void color_36() {
  c = color(180, 127, 181);
}

public void color_37() {
  c = color(209, 126, 170);
}

public void color_38() {
  c = color(210, 130, 159);
}

public void color_39() {
  c = color(222, 126, 153);
}

public void basic_01() {
  c = color(255, 0, 0);
}

public void basic_02() {
  c = color(0, 255, 0);
}

public void basic_03() {
  c = color(0, 0, 255);
}

public void basic_04() {
  c = color(228, 0, 127);
}

public void basic_05() {
  c = color(255, 241, 0);
}

public void basic_06() {
  c = color(0, 160, 233);
}

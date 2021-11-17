#include <Arduboy2.h>
#include <Arduboy2Audio.h>
#include <ArduboyTones.h>

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

int gameState = 0;

int playerSpeed = 2.5;
int playerx = 60;

int enemySpeed = 1;
int enemyx = 60;
int enemyDirection = 1;

int enemyMissilex;
int enemyMissiley;
int enemyMissileFired = false;

int playerMissilex;
int playerMissiley;
int playerMissileFired = false;

int playerMissileSpeed = 2;
int enemyMissileSpeed = 2;

int playerScore = 0;
int enemyScore = 0;

bool playerHurt = false;
int playerHurtTimer = 0;
int enemyHurtTimer = 0;
bool enemyHurt = false;

bool darkMode = false;

const uint16_t successfulHitSound[] PROGMEM =
{
  NOTE_C4,100,NOTE_D4,100,NOTE_E4,100,NOTE_A4,200,NOTE_F4,200,TONES_END
};
const uint16_t playerDamagedSound[] PROGMEM = 
{
  NOTE_C4,100,NOTE_B3,100,NOTE_AS3,100,NOTE_A3,100,NOTE_GS3,500,TONES_END
};

const uint16_t titleMusic[] PROGMEM = 
{
  NOTE_C5,300,NOTE_C5,300,NOTE_E5,300,NOTE_E5,300,NOTE_A4,300,NOTE_A4,300,NOTE_C5,300,NOTE_C5,300,NOTE_D5,300,NOTE_D5,300,NOTE_F5,300,NOTE_F5,300,NOTE_G4,300,NOTE_G4,300,NOTE_B4,300,NOTE_B4,  300,TONES_END
};
const uint8_t PROGMEM titleimage[] = {
128, 64,
0x00, 0x00, 0x00, 0xf8, 0x10, 0x20, 0x10, 0xf8, 0x00, 0xf8, 0x48, 0x48, 0x48, 0x00, 0xf8, 0x08, 0x08, 0x88, 0x88, 0x00, 0xf8, 0x48, 0x48, 0xf8, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x10, 0x20, 0x10, 0xf8, 0x00, 0x08, 0x08, 0xf8, 0x08, 0x08, 0x00, 0x70, 0x88, 0x88, 0x88, 0x08, 0x00, 0x70, 0x88, 0x88, 0x88, 0x08, 0x00, 0x08, 0x08, 0xf8, 0x08, 0x08, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x48, 0x48, 0x48, 0x00, 0x70, 0x88, 0x88, 0x88, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x07, 0x04, 0x04, 0x04, 0x00, 0x07, 0x04, 0x04, 0x04, 0x07, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x04, 0x04, 0x07, 0x04, 0x04, 0x00, 0x04, 0x04, 0x04, 0x04, 0x03, 0x00, 0x04, 0x04, 0x04, 0x04, 0x03, 0x00, 0x04, 0x04, 0x07, 0x04, 0x04, 0x00, 0x07, 0x04, 0x04, 0x04, 0x04, 0x00, 0x07, 0x04, 0x04, 0x04, 0x00, 0x04, 0x04, 0x04, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0x60, 0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0x60, 0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xe0, 0x60, 0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0x60, 0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x7e, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x00, 0x38, 0xfe, 0x7c, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe7, 0xe7, 0xfe, 0xfe, 0xf9, 0xf9, 0xf9, 0xf9, 0xfe, 0xfe, 0xe7, 0xe7, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1e, 0x1e, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1f, 0x1f, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const uint8_t PROGMEM player[] = {
8, 8,
0xff, 0xff, 0x9d, 0x9f, 0x9f, 0xdd, 0xff, 0xff, 
};

const uint8_t PROGMEM enemy[] = {
8, 8,
0xff, 0xf7, 0xbd, 0xbb, 0xbb, 0xbd, 0xf7, 0xff, 
};

const uint8_t PROGMEM enemyhurt[] = {
8, 8,
0xff, 0x93, 0x9e, 0x9d, 0x9d, 0x9e, 0x93, 0xff, 
};
const uint8_t PROGMEM playerhurt[] = {
8, 8,
0xff, 0x9f, 0x99, 0x9f, 0x9f, 0x99, 0x9f, 0xff, 
};



void setup()
{
  arduboy.begin();
  arduboy.clear();
  
  arduboy.setFrameRate(60);
}

void loop()
{
  
  if(!arduboy.nextFrame())
  {
    return;
  }
  
  arduboy.clear();
  
  arduboy.pollButtons();
  
  switch(gameState)
  {
    case 0:
      title();
      break;
    case 1:
      gameplay();
      break;
    case 2:
      //WIN
      
      arduboy.print("YOU WIN!\n\n\n\nPRESS A/B\nTO PLAY AGAIN");
      if(arduboy.justPressed(A_BUTTON)||arduboy.justPressed(B_BUTTON))
      {
        gameState = 1;
      }
      
      break;
    case 3:
      //LOSE
      
      arduboy.print("YOU LOSE!\n\n\n\nPRESS A/B\nTO PLAY AGAIN");
      if(arduboy.justPressed(A_BUTTON)||arduboy.justPressed(B_BUTTON))
      {
        gameState = 1;
      }
      break;
  }  
  arduboy.display();
}

void title()
{
  
  Sprites::drawOverwrite(0,0,titleimage,0);
  
  arduboy.print("\n\n\n\n\n\n\nMikmoomamimocki");
  
  arduboy.setCursor(85,20);
  arduboy.print("A/B TO");
  arduboy.setCursor(85,30);
  arduboy.print("START");
  arduboy.setCursor(20,40);
  arduboy.print("DARK ");
  if(darkMode)
  {
    arduboy.print("ON");
  }
  else
  {
    arduboy.print("OFF");
  }
  arduboy.setCursor(80,40);
  arduboy.print("MUTE ");
  if(arduboy.audio.enabled())
  {
    arduboy.print("OFF");
  }
  else
  {
    arduboy.print("ON");
  }
  
  if(arduboy.pressed(A_BUTTON)||arduboy.pressed(B_BUTTON))
  {
    arduboy.initRandomSeed();
    gameState++;
  }
  if(arduboy.justPressed(LEFT_BUTTON)||arduboy.justPressed(RIGHT_BUTTON))
  {
    if(darkMode)
    {
      darkMode = false;
    }
    else
    {
      darkMode = true;
    }
  }
  if(arduboy.justPressed(UP_BUTTON)||arduboy.justPressed(DOWN_BUTTON))
  {
    arduboy.audio.toggle();
  }

  if(!sound.playing())
  {
    sound.tones(titleMusic);
  }
}

void gameplay()
{
  //Score display
  arduboy.print(enemyScore);
  arduboy.print("\n\n\n\n\n\n\n");
  arduboy.print(playerScore);
  
  
  //Win/lose
  
  if(playerScore == 10)
  {
    reset();
    gameState = 2;
  }
  if(enemyScore == 10)
  {
    reset();
    gameState = 3;
  }
  
  //Player
  
  if(arduboy.pressed(LEFT_BUTTON))
  {
    playerx-=playerSpeed;
  }
  if(arduboy.pressed(RIGHT_BUTTON))
  {
    playerx+=playerSpeed;
  }
  if(arduboy.justPressed(A_BUTTON)||arduboy.justPressed(B_BUTTON))
  {
    if(!playerMissileFired)
    {
      playerMissileFired = true;
      
      playerMissilex = playerx+3;
      playerMissiley = 56;
    }
  }
  if(playerMissileFired)
  {
    if(playerMissiley < -7)
    {
      playerMissileFired = false;
    }
    playerMissiley-=playerMissileSpeed;
    
    arduboy.fillRect(playerMissilex,playerMissiley,2,6,WHITE);
  }
  
  if(playerx>120)
  {
    playerx = 120;
  }
  if(playerx<0)
  {
    playerx = 0;
  }
  
  if(playerHurt)
  {
    Sprites::drawOverwrite(playerx,56,playerhurt,0);
    if(!darkMode)
    {
      arduboy.setRGBled(255,0,0);
    }
  }
  else
  {
    Sprites::drawOverwrite(playerx,56,player,0);
    arduboy.setRGBled(0,0,0);
  }
  
  
  
  
  
  //Enemy
  
  
  enemyx+=enemySpeed*enemyDirection;
  
  
  if(enemyx>120)
  {
    enemyx = 120;
  }
  if(enemyx<0)
  {
    enemyx = 0;
  }
  if(enemyx==120 || enemyx==0)
  {
    enemyDirection = enemyDirection * -1;
  }
  
  int enemyChangeDirection = random(1,126);
  if(enemyChangeDirection == 1)
  {
    enemyDirection = enemyDirection * -1;
  }
  
  
  if(enemyx==playerx || enemyx==playerx+1  ||enemyx==playerx-1  )
  {
    if(enemyMissileFired == false)
    {
      enemyMissileFired = true;
      enemyMissilex = enemyx+3;
      enemyMissiley = 0;
    }
  }
  
  if(enemyMissileFired)
  {
    if(enemyMissiley > 71)
    {
      enemyMissileFired = false;
    }
    enemyMissiley+=enemyMissileSpeed;
    
    arduboy.fillRect(enemyMissilex,enemyMissiley,2,6,WHITE);
  }
  
  if(enemyHurt)
  {
    Sprites::drawOverwrite(enemyx,0,enemyhurt,0);
    if(!playerHurt && !darkMode)
    {
      arduboy.setRGBled(0,255,0);
    }
  }
  else
  {
    Sprites::drawOverwrite(enemyx,0,enemy,0);
  }
  
  
  
  //Hurt sprite change
  
  if(enemyHurt)
  {
    if(enemyHurtTimer == 60)
    {
      enemyHurt = false;
      enemyHurtTimer = 0;
    }
    else
    {
      enemyHurtTimer++;
    }
  }
  
  if(playerHurt)
  {
    if(playerHurtTimer == 60)
    {
      playerHurt = false;
      playerHurtTimer = 0;
    }
    else
    {
      playerHurtTimer++;
    }
  }
  
  
  //Collision and Scoring
  
  if(enemyMissiley+6 == 56)
  {
    if(enemyMissilex == playerx || enemyMissilex == playerx+1 || enemyMissilex == playerx+2 ||enemyMissilex == playerx+3 ||enemyMissilex == playerx+4 ||enemyMissilex == playerx+5 ||enemyMissilex == playerx+6 ||enemyMissilex == playerx+7 ||enemyMissilex == playerx+8)
    {
      enemyMissileFired = false;
      enemyMissiley = 128;
      playerHurt = true;
      sound.tones(playerDamagedSound);
      enemyScore++;
    }
  }
  
  if(playerMissiley-6 == 0)
  {
    if(playerMissilex == enemyx || playerMissilex == enemyx+1 || playerMissilex == enemyx+2 ||playerMissilex == enemyx+3 ||playerMissilex == enemyx+4 ||playerMissilex == enemyx+5 ||playerMissilex == enemyx+6 ||playerMissilex == enemyx+7 ||playerMissilex == enemyx+8)
    {
      playerMissileFired = false;
      playerMissiley = -128;
      enemyHurt = true;
       sound.tones(successfulHitSound);
      playerScore++;
    }
  }
}

void reset()
{
  playerx = 60;
  enemyx = 60;
  enemyDirection = 1;
  playerMissileFired = false;
  enemyMissileFired = false;
  playerScore = 0;
  enemyScore = 0;
  playerHurtTimer = 0;
  enemyHurtTimer = 0;
  playerHurt = false;
  enemyHurt = false;
}

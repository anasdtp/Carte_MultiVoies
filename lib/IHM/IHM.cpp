#include "IHM.h"
#include "logo.h"

#ifndef min
  #define min(a,b) ((a < b)?(a): (b))
#endif

#ifndef max
  #define max(a,b) ((a > b)?(a): (b))
#endif

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_PIN_RESET);

void initIHM(){
    Wire.begin(SDA_OLED_PIN, SCL_OLED_PIN, 400000);
    delay(250); // wait for the OLED to power up
    while(!display.begin(i2c_Address, true)) { // Address 0x3C for 128x64, reset pin 23
      Serial.println(F("SSD1309 allocation failed"));
      delay(250);
  }
  display.display();
  display.clearDisplay();
  display.display();
}

void printMidOLED(String text, int textSize, int y) {
  display.clearDisplay();
  display.setTextSize(textSize);
  display.setTextColor(SH110X_WHITE);
  
  int charWidth = 6 * textSize;  // Largeur approximative d'un caractère en pixels
  int maxCharsPerLine = SCREEN_WIDTH / charWidth;  // Nombre maximum de caractères par ligne
  
  int lineHeight = 8 * textSize;  // Hauteur approximative d'une ligne de texte en pixels
  
  // Découper le texte en lignes en fonction des retours à la ligne (\n)
  int startIdx = 0;
  int currentY = y;
  while (startIdx < text.length()) {
    int endIdx = text.indexOf('\n', startIdx);
    if (endIdx == -1) {
      endIdx = text.length();
    }
    String line = text.substring(startIdx, endIdx);

    // Si la ligne est trop longue, découper en plusieurs sous-lignes
    while (line.length() > maxCharsPerLine) {
      String subLine = line.substring(0, maxCharsPerLine);
      int x = (SCREEN_WIDTH - (subLine.length() * charWidth)) / 2;
      display.setCursor(x, currentY);
      display.println(subLine);
      currentY += lineHeight;
      line = line.substring(maxCharsPerLine);
    }
    
    // Afficher la ligne ou la sous-ligne restante
    int x = (SCREEN_WIDTH - (line.length() * charWidth)) / 2;
    display.setCursor(x, currentY);
    display.println(line);
    currentY += lineHeight;

    // Passer au prochain segment après le retour à la ligne
    startIdx = endIdx + 1;
  }
  
  display.display();
}
String buffer = ""; // Buffer interne pour stocker le texte
int maxLines = SCREEN_HEIGHT / (8 * 1); // Nombre maximum de lignes affichables

void printMidOLED(String text) {
  int textSize = 1; // Taille de texte fixe
  int y = 0; // Position y de base
  
  display.setTextSize(textSize);
  display.setTextColor(SH110X_WHITE);
  
  int charWidth = 6 * textSize;  // Largeur approximative d'un caractère en pixels
  int maxCharsPerLine = SCREEN_WIDTH / charWidth;  // Nombre maximum de caractères par ligne
  
  int lineHeight = 8 * textSize;  // Hauteur approximative d'une ligne de texte en pixels
  
  // Découper le texte en lignes en fonction des retours à la ligne (\n)
  int startIdx = 0;
  while (startIdx < text.length()) {
    int endIdx = text.indexOf('\n', startIdx);
    if (endIdx == -1) {
      endIdx = text.length();
    }
    String line = text.substring(startIdx, endIdx);

    // Si la ligne est trop longue, découper en plusieurs sous-lignes
    while (line.length() > maxCharsPerLine) {
      String subLine = line.substring(0, maxCharsPerLine);
      buffer += subLine + "\n";
      line = line.substring(maxCharsPerLine);
    }
    
    // Ajouter la ligne ou la sous-ligne restante au buffer
    buffer += line + "\n";

    // Passer au prochain segment après le retour à la ligne
    startIdx = endIdx + 1;
  }
  
  // Découper le buffer en lignes
  int lineCount = 0;
  startIdx = 0;
  while (startIdx < buffer.length()) {
    int endIdx = buffer.indexOf('\n', startIdx);
    if (endIdx == -1) {
      endIdx = buffer.length();
    }
    lineCount++;
    startIdx = endIdx + 1;
  }

  // Si le nombre de lignes dépasse le maximum, supprimer les premières lignes
  if (lineCount > maxLines) {
    int linesToRemove = lineCount - maxLines;
    startIdx = 0;
    while (linesToRemove > 0) {
      int endIdx = buffer.indexOf('\n', startIdx);
      if (endIdx == -1) {
        break;
      }
      startIdx = endIdx + 1;
      linesToRemove--;
    }
    buffer = buffer.substring(startIdx);
  }

  // Afficher le buffer ligne par ligne
  display.clearDisplay();
  startIdx = 0;
  int currentY = y;
  while (startIdx < buffer.length()) {
    int endIdx = buffer.indexOf('\n', startIdx);
    if (endIdx == -1) {
      endIdx = buffer.length();
    }
    String line = buffer.substring(startIdx, endIdx);
    int x = (SCREEN_WIDTH - (line.length() * charWidth)) / 2;
    display.setCursor(x, currentY);
    display.println(line);
    currentY += lineHeight;
    startIdx = endIdx + 1;
  }
  
  display.display();
}

void displayLogo(){
  display.clearDisplay();
  display.drawBitmap((SCREEN_WIDTH - 91) / 2, (SCREEN_HEIGHT - 64) / 2, assystem, 91, 64, SH110X_WHITE);
  display.display();
}
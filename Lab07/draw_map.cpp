#include <wx/wx.h>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
 wxMemoryDC memDC;
 memDC.SelectObject(MemoryBitmap);
 memDC.SetBackground(*wxWHITE_BRUSH);
 memDC.Clear();
    
 // demo.....
 memDC.SetPen(*wxBLACK_PEN);
 memDC.SetBrush(*wxTRANSPARENT_BRUSH);
    
 if (MappingType == 1) memDC.DrawText("Mapa niebiesko-czerwona...", wxPoint(10, 30));
 if (MappingType == 2) memDC.DrawText("Mapa niebiesko-zielono-czerwona...", wxPoint(10, 30));
 if (MappingType == 3) memDC.DrawText("Mapa szara...", wxPoint(10, 30));
  
 if (Contour) memDC.DrawText("Kontury...", wxPoint(10, 10));
 if (ShowPoints) memDC.DrawText("Punkty...", wxPoint(10, 50));
      
}

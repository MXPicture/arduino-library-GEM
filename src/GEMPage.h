/*
  GEMPage - menu page (or level) for GEM library. Consists of a list of menu items.

  GEM (a.k.a. Good Enough Menu) - Arduino library for creation of graphic multi-level menu with
  editable menu items, such as variables (supports int, byte, float, double, bool, char[17] data types)
  and option selects. User-defined callback function can be specified to invoke when menu item is saved.
  
  Supports buttons that can invoke user-defined actions and create action-specific
  context, which can have its own enter (setup) and exit callbacks as well as loop function.

  Supports:
  - AltSerialGraphicLCD library by Jon Green (http://www.jasspa.com/serialGLCD.html);
  - U8g2 library by olikraus (https://github.com/olikraus/U8g2_Arduino);
  - Adafruit GFX library by Adafruit (https://github.com/adafruit/Adafruit-GFX-Library).

  For documentation visit:
  https://github.com/Spirik/GEM

  Copyright (c) 2018-2025 Alexander 'Spirik' Spiridonov

  This file is part of GEM library.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public License
  along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_GEMPAGE
#define HEADER_GEMPAGE

#include <Arduino.h>
#include "GEMAppearance.h"
#include "GEMItem.h"

// Macro constant (alias) for the last possible position that menu item can be added at
#define GEM_LAST_POS 255

// Macro constant (alias) for modifier of GEMPage::addMenuItem() method for the case when all menu items should be considered
#define GEM_ITEMS_TOTAL true

// Macro constant (alias) for modifier of GEMPage::addMenuItem() method for the case when only visible menu items should be considered
#define GEM_ITEMS_VISIBLE false

// Declaration of GEMPage class
class GEMPage {
  friend class GEM;
  friend class GEM_u8g2;
  friend class GEM_adafruit_gfx;
  friend class GEMItem;
  public:
    /* 
      @param 'title_' - title of the menu page displayed at top of the screen
      @param 'exitAction_' - pointer to callback function executed when GEM_KEY_CANCEL is pressed while being on top level menu page
      @param 'parentMenuPage_' - reference to parent level menu page (to know where to go back to when Back button is pressed)
    */
    GEMPage(const char* title_ = "");
    GEMPage(const char* title_, void (*exitAction_)());
    GEMPage(const char* title_, GEMPage& parentMenuPage_);
    GEM_VIRTUAL GEMPage& addMenuItem(GEMItem& menuItem, byte pos = GEM_LAST_POS, bool total = GEM_ITEMS_TOTAL);  // Add menu item to menu page (optionally at specified index out of total or only visible items)
    GEM_VIRTUAL GEMPage& setParentMenuPage(GEMPage& parentMenuPage);        // Specify parent level menu page (to know where to go back to when Back button is pressed)
    GEM_VIRTUAL GEMPage& setTitle(const char* title_);                      // Set title of the menu page
    GEM_VIRTUAL const char* getTitle();                                     // Get title of the menu page
    GEMPage& setAppearance(GEMAppearance* appearance);                      // Set appearance of the menu page
    GEM_VIRTUAL GEMItem* getMenuItem(byte index, bool total = false);       // Get pointer to menu item by index (counting hidden ones if total set to true)
    GEM_VIRTUAL GEMItem* getCurrentMenuItem();                              // Get pointer to current menu item
    GEM_VIRTUAL byte getCurrentMenuItemIndex();                             // Get index of current menu item
    GEMPage& setCurrentMenuItemIndex(byte index);                           // Set index of current menu item
    GEM_VIRTUAL byte getItemsCount(bool total = false);                     // Get items count of the menu page (counting hidden ones if total set to true)
  protected:
    const char* title;
    byte currentItemNum = 0;                                                // Currently selected (focused) menu item of the page
    byte itemsCount = 0;                                                    // Items count excluding hidden ones
    byte itemsCountTotal = 0;                                               // Items count incuding hidden ones
    GEM_VIRTUAL int getMenuItemNum(GEMItem& menuItem, bool total = false);  // Find index of the supplied menu item
    void hideMenuItem(GEMItem& menuItem);
    void showMenuItem(GEMItem& menuItem);
    GEM_VIRTUAL void removeMenuItem(GEMItem& menuItem);                     // Remove menu item from menu page
    GEMItem* _menuItem = nullptr;                                           // First menu item of the page (the following ones are linked from within one another)
    GEMItem _menuItemBack {"", static_cast<GEMPage*>(nullptr)};             // Local instance of Back button (created when parent level menu page is specified through
                                                                            // setParentMenuPage(); always becomes the first menu item in a list)
    void (*exitAction)() = nullptr;
    GEMAppearance* _appearance = nullptr;
};
  
#endif

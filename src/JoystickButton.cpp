
#include "JoystickButton.h"
#include "Arduino.h"


JoyButton::JoyButton(int VRX_PIN, int VRY_PIN, int SW_PIN, int NUM_ITEMS);
:  _button(SW_PIN)
{
   _VRX_PIN = VRX_PIN;
   _VRY_PIN = VRY_PIN;
   _SW_PIN = SW_PIN;

     _NUM_ITEMS = NUM_ITEMS;



    _item_selected = 0;
    _current_screen = 0;

    _button_select_clicked = 0;
    _button_up_clicked = 0;
    _button_down_clicked = 0;

}
void JoyButton::setup() {
 pinMode(_VRX_PIN, INPUT);
 pinMode(_VRY_PIN, INPUT);
 pinMode(_SW_PIN, INPUT_PULLUP);

 _button.setDebounceTime(200);
}

void JoyButton::update() {
_button.loop();

int X = analogRead(_VRX_PIN);
int Y = analogRead(_VRY_PIN);


//select button logic
  if (_button.isPressed()) {
    if ((digitalRead(_SW_PIN) == LOW) && (_button_select_clicked == 0)) { // select button clicked, jump between screens
     _button_select_clicked = 1; // set button to clicked to only perform the action once
     if (_current_screen == 0) {_current_screen = 1;} // menu items screen --> screenshots screen
      else if (_current_screen == 1) {_current_screen = 2;} // screenshots screen --> qr codes screen
     else {_current_screen = 0;} // qr codes screen --> menu items screen 
  }
    // TODO do something here
  }

  if (_button.isReleased()) {
   _button_select_clicked = 0;
    // TODO do something here
  }


//up down logic
    if (Y>700) { 
      _button_up_clicked = 1;
    }
    else if (Y<300) { 
      _button_down_clicked=1;
    }

// right left logic
    if (X>700) { 
      _button_up_clicked = 1;
    }
    else if (X<300) { 
      _button_down_clicked=1;
    }

    //up click logic
 if ((_button_up_clicked == 1) && (Y>700)) {
 switch (_current_screen) {
 case 0:
        _item_selected = _item_selected - 1; // select previous item
      
        if (_item_selected < 0) { // if first item was selected, jump to last item
          _item_selected = _NUM_ITEMS-1;
          delay(650);
          }
    break;
      
  }
 }
  // unclicks if no longer held
  else if ((_button_up_clicked == 1) && (Y<700)) {
    _button_up_clicked = 0;
}

//makes the joystick do a down action also changes what happens based on screen, 
// and it can be held down to do an action every 650 ms

if ((_button_down_clicked == 1) && (Y<300)) {
 switch (_current_screen) {
 case 0:
        _item_selected = _item_selected + 1; // select next item
        _button_down_clicked = 1; // set button to clicked to only perform the action once
        if (_item_selected >= _NUM_ITEMS) { // last item was selected, jump to first menu item
          _item_selected = 0;
    _button_up_clicked = 0;
}
          delay(650);
    break;
     }
  }
  else if ((_button_down_clicked == 1) && (X>300)) {
    _button_down_clicked = 0;
}
// right left click logic

if ((_button_up_clicked == 1) && (X>700)) {
 switch (_current_screen) {
 case 0:
       /* _item_selected = _item_selected - 1; // select previous item
      
        if (_item_selected < 0) { // if first item was selected, jump to last item
          _item_selected = _NUM_ITEMS-1;
          delay(650); */
    break;
    }
      
  }
  // unclicks if no longer held
  else if ((_button_up_clicked == 1) && (X<700)) {
    _button_up_clicked = 0;
}

//makes the joystick do a down action also changes what happens based on screen, 
// and it can be held down to do an action every 650 ms

if ((_button_down_clicked == 1) && (X<300)) {
 switch (_current_screen) {
 case 0:
        /*_item_selected = _item_selected + 1; // select next item
        _button_down_clicked = 1; // set button to clicked to only perform the action once
        if (_item_selected >= _NUM_ITEMS) { // last item was selected, jump to first menu item
          _item_selected = 0;
    _button_up_clicked = 0;
}
          delay(650); */
    break;
     }
  }
  else if ((_button_down_clicked == 1) && (X>300)) {
    _button_down_clicked = 0;
}

}
int JoyButton::ItemSelected() {

return _item_selected;
}

int JoyButton::CurrentScreen() {

return _current_screen;
}


int JoyButton::readX() {

return analogRead(_VRX_PIN);
}


int JoyButton::readY() {

return analogRead(_VRY_PIN);

}

 

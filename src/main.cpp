#include <iostream>
#include "../include/display_manager.h"

int main() {

	DisplayManager disp_man("./data/.cfg");
	Property property("./data/property.dat", "./data/plants.dat");

	disp_man.open(property);

	// Save stuff to the property
}
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Vehicle_Vtable {
	void (*describe)(void*);
	bool (*allowedOnFreeway)(void*);
	void (*turn)(void*, char*);
} Vehicle_Vtable;

typedef struct Vehicle_Data {
	char *color;
} Vehicle_Data;

typedef struct Vehicle {
	Vehicle_Vtable *vtable;
	Vehicle_Data;
} Vehicle;

void Vehicle_describe(Vehicle* this) {
	printf("A %s vehicle.\n", this->color);
}

bool Vehicle_allowedOnFreeway() {
	return false;
}

void Vehicle_turn(Vehicle* this, char *direction) {
	printf("Turning %s.\n", direction);
}

Vehicle_Vtable Vehicle_vtable = {
	(void*) Vehicle_describe,
					  // ^ We need to cast the method here to hide warnings
	(void*) Vehicle_allowedOnFreeway,
	(void*) Vehicle_turn
};

Vehicle* Vehicle_Vehicle(Vehicle* this, char *color) {
	this->vtable = &Vehicle_vtable;

	this->color = color;

	return this;
}

typedef struct Bike_Vtable {
	Vehicle_Vtable;
	bool (*canGoOffroad)(void*);
} Bike_Vtable;

typedef struct Bike_Data {
	Vehicle_Data;
	bool isMountainBike;
} Bike_Data;

typedef struct Bike {
	Bike_Vtable *vtable;
	Bike_Data;
} Bike;

void Bike_describe(Bike* this) {
	printf("A %s bike makes ringring.\n", this->color);
}

bool Bike_canGoOffroad(Bike* this) {
	return this->isMountainBike;
}

Bike_Vtable Bike_vtable = {
	(void*) Bike_describe, // override describe
	(void*) Vehicle_allowedOnFreeway, // inherit allowedOnFreeway from vehicle
	(void*) Vehicle_turn,
	(void*) Bike_canGoOffroad
};

Bike* Bike_Bike(Bike* this, char *color, bool isMountainBike) {
	Vehicle_Vehicle((Vehicle*)this, color);
	this->vtable = &Bike_vtable;

	this->isMountainBike = isMountainBike;

	return this;
}

typedef struct Car_Vtable {
	Vehicle_Vtable;
} Car_Vtable;

typedef struct Car_Data {
	Vehicle_Data;
	char *brand;
} Car_Data;

typedef struct Car {
	Car_Vtable *vtable;
	Car_Data;
} Car;

void Car_describe(Car* this){
	printf("A %s %s makes vroom.\n", this->color, this->brand);
}

bool Car_allowedOnFreeway() {
	return true;
}

Car_Vtable Car_vtable = {
	(void*) Car_describe,
	(void*) Car_allowedOnFreeway,
	(void*) Vehicle_turn
};

Car* Car_Car(Car* this, char *color, char *brand) {
	Vehicle_Vehicle((Vehicle*)this, color);
	this->vtable = &Car_vtable;

	this->brand = brand;

	return this;
}

typedef struct Train_Vtable {
	Vehicle_Vtable;
	bool (*isSteamEngine)(void*);
} Train_Vtable;

typedef struct Train_Data {
	Vehicle_Data;
	int buildYear;
} Train_Data;

typedef struct Train {
	Train_Vtable *vtable;
	Train_Data;
} Train;

bool isSteamEngine(Train* this) {
	return this->buildYear < 1934;
}

void Train_describe(Train* this) {
	if (isSteamEngine) {
		printf("A %s train makes choo-choo.\n", this->color);
	} else {
		printf("A %s train makes zoosh-zoosh.\n", this->color);
	}
}

void Train_turn(Train* this, char *direction) {
	printf("A train can't simply turn!\n");
}

Train_Vtable Train_vtable = {
	(void*) Train_describe,
	(void*) Vehicle_allowedOnFreeway,
	(void*) Train_turn,
	(void*) isSteamEngine
};

Train* Train_Train(Train* this, char *color, int buildYear) {
	Vehicle_Vehicle((Vehicle*)this, color);
	this->vtable = &Train_vtable;

	this->buildYear = buildYear;

	return this;
}

typedef struct SportsCar_Vtable {
	Car_Vtable;
	void (*roarEngine)(void*);
} SportsCar_Vtable;

typedef struct SportsCar_Data {
	Car_Data;
	int horsePowers;
} SportsCar_Data;

typedef struct SportsCar {
	SportsCar_Vtable *vtable;
	SportsCar_Data;
} SportsCar;

void SportsCar_describe(SportsCar* this) {
	printf("A %s %s makes VROOOM!\n", this->color, this->brand);
}

void SportsCar_roarEngine(SportsCar* this) {
	printf("%i horse powers make VROOOM!\n", this->horsePowers);
}

SportsCar_Vtable SportsCar_vtable = {
	(void*) SportsCar_describe,
	(void*) Car_allowedOnFreeway,
	(void*) Vehicle_turn,
	(void*) SportsCar_roarEngine
};

SportsCar* SportsCar_SportsCar(SportsCar* this, char *color, char *brand, int horsePowers) {
	Car_Car((Car*)this, color, brand);
	this->vtable = &SportsCar_vtable;
	this->horsePowers = horsePowers;

	return this;
}

int main(int argc, char **argv) {
	Vehicle *a = Vehicle_Vehicle((Vehicle*)malloc(sizeof(Vehicle)), "red");
	a->vtable->describe(a);
	a->vtable->turn(a, "right");
	printf("a %s enter the freeway.\n", a->vtable->allowedOnFreeway(a) ? "can" : "cannot");

	Bike *b = Bike_Bike((Bike*)malloc(sizeof(Bike)), "green", true);
	b->vtable->describe(b);
	b->vtable->turn(b, "right");
	printf("b %s enter the freeway.\n", b->vtable->allowedOnFreeway(b) ? "can" : "cannot");
	printf("b %s go offroad.\n", b->vtable->canGoOffroad(b) ? "can" : "cannot");

	Car *c = Car_Car((Car*)malloc(sizeof(Car)), "yellow", "Volkswagen");
	c->vtable->describe(c);
	c->vtable->turn(c, "left");
	printf("c %s enter the freeway.\n", c->vtable->allowedOnFreeway(c) ? "can" : "cannot");

	Train *d = Train_Train((Train*)malloc(sizeof(Train)), "black", 2014);
	d->vtable->describe(d);
	d->vtable->turn(d, "left");
	printf("d %s enter the freeway.\n", d->vtable->allowedOnFreeway(d) ? "can" : "cannot");
	printf("d %s using a steam engine.\n", d->vtable->isSteamEngine(d) ? "is" : "is not");

	SportsCar *e = SportsCar_SportsCar((SportsCar*)malloc(sizeof(SportsCar)), "red", "Porsche", 600);
	e->vtable->describe(e);
	e->vtable->turn(e, "right");
	e->vtable->roarEngine(e);
	printf("e %s enter the freeway.\n", e->vtable->allowedOnFreeway(e) ? "can" : "cannot");
}

class Vehicle {
	// Usually, Vehicle would be defined in Vehicle.java.
	// For the sake of having everything in one file, we have it as a non-public
	// class here.

	public String color;

	public Vehicle(String color) {
		this.color = color;
	}

	public void describe() {
		System.out.println("A " + color + " vehicle.");
	}

	public boolean allowedOnFreeway() {
		return false; // We don't want unspecified vehicles on our highways
	}

	public void turn(String direction) {
		System.out.println("Turning " + direction + ".");
	}
}

class Bike extends Vehicle {
	public boolean isMountainBike;

	public Bike(String color, boolean isMountainBike) {
		super(color);
		this.isMountainBike = isMountainBike;
	}

	public void describe() {
		System.out.println("A " + color + " bike makes ringring.");
	}

	public boolean canGoOffroad() {
		return isMountainBike;
	}
}

class Car extends Vehicle {
	public String brand;

	public Car(String color, String brand) {
		super(color);
		this.brand = brand;
	}

	public void describe() {
		System.out.println("A " + color + " " + brand + " makes vrooom.");
	}

	public boolean allowedOnFreeway() {
		return true;
	}
}

class Train extends Vehicle {
	public int buildYear;

	public Train(String color, int buildYear) {
		super(color);
		this.buildYear = buildYear;
	}

	public boolean isSteamEngine() {
		return this.buildYear < 1934;
	}

	public void describe() {
		if(isSteamEngine()) {
			// steam engine
			System.out.println("A " + color + " train makes choo-choo.");
		} else {
			// diesel engine
			System.out.println("A " + color + " train makes zoosh-zoosh.");
			// at least it does according to http://www.writtensound.com/index.php?term=train ;)
		}
	}

	public void turn(String direction) {
		System.out.println("A train can't simply turn!");
	}
}

class SportsCar extends Car {
	public int horsePowers;

	public SportsCar(String color, String brand, int horsePowers) {
		super(color, brand);
		this.horsePowers = horsePowers;
	}

	public void describe() {
		System.out.println("A " + color + " " + brand + " makes VROOOM!");
	}

	public void roarEngine() {
		System.out.println(horsePowers + " horse powers make VROOOM!");
	}
}

public class VehicleTest {
	public static void main(String[] args) {
		Vehicle a = new Vehicle("red");
		a.describe();
		a.turn("right");
		System.out.println("a " + (a.allowedOnFreeway() ? "can" : "cannot") + " enter the freeway.");

		Bike b = new Bike("green", true);
		b.describe();
		b.turn("right");
		System.out.println("b " + (b.allowedOnFreeway() ? "can" : "cannot") + " enter the freeway.");
		System.out.println("b " + (b.canGoOffroad() ? "can" : "cannot") + " go offroad.");

		Car c = new Car("yellow", "Volkswagen");
		c.describe();
		c.turn("left");
		System.out.println("c " + (c.allowedOnFreeway() ? "can" : "cannot") + " enter the freeway.");

		Train d = new Train("black", 2014);
		d.describe();
		d.turn("left");
		System.out.println("d " + (d.allowedOnFreeway() ? "can" : "cannot") + " enter the freeway.");
		System.out.println("d " + (d.isSteamEngine() ? "is" : "is not") + " using a steam engine.");

		SportsCar e = new SportsCar("red", "Porsche", 600);
		e.describe();
		e.turn("right");
		e.roarEngine();
		System.out.println("e " + (c.allowedOnFreeway() ? "can" : "cannot") + " enter the freeway.");

	}
}
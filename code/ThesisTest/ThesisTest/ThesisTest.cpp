#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

const int max_length_one_line = 80;

struct Point {
	int x, y;
	Point() {
	}

	Point(int x, int y) : x(x), y(y) {

	}
};
typedef Point Door;
typedef Point Entry;

struct Wall {
	Point p1, p2;
};
typedef Wall OuterWall;

struct Room {
	char name[10];
	int wall_num;
	vector<Point> vertexes;
	Door door;

	// to indicate whether one of the walls is reachable 
	vector<bool> reachable;
};

struct Elevator {
	char name[20];
	Point p[4];
	Entry entry;
};

struct Stair {
	char name[20];
	Point p[4];
	Entry entry;
};

int outerwall_num;
vector<Point> outerwall_points;

int room_num;
vector<Room> rooms;

int elevator_num;
vector<Elevator> elevators;

int stair_num;
vector<Stair> stairs;

Door entry;

void ReadOneLine(char *dest) {
	while (cin.getline(dest, max_length_one_line)) {
		// skip the blank lines
		if (strlen(dest) < 1) {
			continue;
		}

		// skip the comment lines
		if ('#' == dest[0]) {
			continue;
		}
		break;
	}
}

void ReadEntryPoint() {
	char oneline[max_length_one_line];
	ReadOneLine(oneline);

	const char *d = ",() ";
	char *p = strtok(oneline, d);
	sscanf(p, "%d", &entry.x);
	p = strtok(NULL, d);
	sscanf(p, "%d", &entry.y);
}

void ReadOutWalls() {
	char oneline[max_length_one_line];
	ReadOneLine(oneline);

	stringbuf buffer;
	istream is(&buffer);
	buffer.sputn(oneline, strlen(oneline));

	// input the outer walls
	//cout << "input the number of outer walls" << endl;
	is >> outerwall_num;

	outerwall_points = vector<Point>(outerwall_num);
	//cout << "input the points of outer walls" << endl;
	ReadOneLine(oneline);

	const char *d = ",() ";
	char *p;
	p = strtok(oneline, d);
	int t = 0;
	while (p) {
		int x, y;
		sscanf(p, "%d", &x);
		p = strtok(NULL, d);
		sscanf(p, "%d", &y);
		outerwall_points[t++] = Point(x, y);
		p = strtok(NULL, d);
	}


}

void ReadRoom(Room &room) {
	char oneline[max_length_one_line];
	ReadOneLine(oneline);

	//cout << "input the name of the room: " << endl;
	strcpy(room.name, oneline);

	//cout << "intput the number of the points of the room" << endl;
	ReadOneLine(oneline);
	stringbuf buffer;
	istream is(&buffer);
	buffer.sputn(oneline, strlen(oneline));
	int point_num;
	is >> point_num;
	room.vertexes = vector<Point>(point_num);

	//cout << "input points of the room:" << endl;
	ReadOneLine(oneline);
	const char *d = ",() ";
	char *p;
	p = strtok(oneline, d);
	int t = 0;
	while (p) {
		int x, y;
		sscanf(p, "%d", &x);
		p = strtok(NULL, d);
		sscanf(p, "%d", &y);
		room.vertexes[t++] = Point(x, y);
		p = strtok(NULL, d);
	}

	//cout << "input the door point: " << endl;
	ReadOneLine(oneline);
	p = strtok(oneline, d);
	sscanf(p, "%d", &room.door.x);
	p = strtok(NULL, d);
	sscanf(p, "%d", &room.door.y);
}

void ReadRooms() {
	char oneline[max_length_one_line];
	ReadOneLine(oneline);

	stringbuf buffer;
	istream is(&buffer);
	buffer.sputn(oneline, strlen(oneline));

	// input the number of rooms
	//cout << "input the number of rooms" << endl;
	is >> room_num;
	rooms = vector<Room>(room_num);
	for(int i = 0; i < room_num; i++) {
		ReadRoom(rooms[i]);
	}
}

void ReadElevator(Elevator &elevator) {
	char oneline[max_length_one_line];
	ReadOneLine(oneline);

	//cout << "input the name of the elevator: " << endl;
	strcpy(elevator.name, oneline);

	//cout << "input the 4 points of the elevator:" << endl;
	ReadOneLine(oneline);
	const char *d = ",() ";
	char *p;
	p = strtok(oneline, d);
	int t = 0;
	while (p) {
		int x, y;
		sscanf(p, "%d", &x);
		p = strtok(NULL, d);
		sscanf(p, "%d", &y);
		elevator.p[t++] = Point(x, y);
		p = strtok(NULL, d);
	}

	//cout << "input the entry point: " << endl;
	ReadOneLine(oneline);
	p = strtok(oneline, d);
	sscanf(p, "%d", &elevator.entry.x);
	p = strtok(NULL, d);
	sscanf(p, "%d", &elevator.entry.y);
}

void ReadElevators() {
	char oneline[max_length_one_line];
	ReadOneLine(oneline);

	stringbuf buffer;
	istream is(&buffer);
	buffer.sputn(oneline, strlen(oneline));

	// input the number of elevators
	//cout << "input the number of elevators" << endl;
	is >> elevator_num;
	elevators = vector<Elevator>(elevator_num);
	for(int i = 0; i < elevator_num; i++) {
		ReadElevator(elevators[i]);
	}
}

void ReadStair(Stair &stair) {
	char oneline[max_length_one_line];
	ReadOneLine(oneline);

	//cout << "input the name of the stair: " << endl;
	strcpy(stair.name, oneline);

	//cout << "input the 4 points of the stair:" << endl;
	ReadOneLine(oneline);
	const char *d = ",() ";
	char *p;
	p = strtok(oneline, d);
	int t = 0;
	while (p) {
		int x, y;
		sscanf(p, "%d", &x);
		p = strtok(NULL, d);
		sscanf(p, "%d", &y);
		stair.p[t++] = Point(x, y);
		p = strtok(NULL, d);
	}

	//cout << "input the entry point: " << endl;
	ReadOneLine(oneline);
	p = strtok(oneline, d);
	sscanf(p, "%d", &stair.entry.x);
	p = strtok(NULL, d);
	sscanf(p, "%d", &stair.entry.y);
}

void ReadStairs() {
	char oneline[max_length_one_line];
	ReadOneLine(oneline);

	stringbuf buffer;
	istream is(&buffer);
	buffer.sputn(oneline, strlen(oneline));

	// input the number of stairs
	//cout << "input the number of stairs" << endl;
	is >> stair_num;
	stairs = vector<Stair>(stair_num);
	for(int i = 0; i < stair_num; i++) {
		ReadStair(stairs[i]);
	}
}

void DistributeNodes() {
}

void BuildPath() {
}

void BestPath() {
}

void DumpEntryPoint() {
	cout << "entry point: " << entry.x << " " << entry.y << endl;
}

void DumpOutWalls() {
	cout << "outer wall number: " << outerwall_num << endl;
	for (Point &p : outerwall_points) {
		cout << "(" << p.x << "," << p.y << "),";
	}
	cout << endl;
}

void DumpRooms() {
	cout << "room number: " << room_num << endl;
	for (Room &room : rooms) {
		cout << room.name << " " << room.vertexes.size() << " points" << endl;
		for (Point &p : room.vertexes) {
			cout << "(" << p.x << "," << p.y << "),";
		}
		cout << endl;
	}
}

void DumpElevators() {
	cout << "elevator number: " << elevator_num << endl;
	for (Elevator &elevator : elevators) {
		cout << elevator.name << ": ";
		for (int i = 0; i < 4; i++) {
			Point p = elevator.p[i];
			cout << "(" << p.x << "," << p.y << "),";
		}
		cout << endl;
		cout << "entry point: " << "(" << elevator.entry.x << "," 
			<< elevator.entry.y << ")" << endl;
	}
}

void DumpStairs() {
	cout << "stair number: " << stair_num << endl;
	for (Stair &stair : stairs) {
		cout << stair.name << ": ";
		for (int i = 0; i < 4; i++) {
			Point p = stair.p[i];
			cout << "(" << p.x << "," << p.y << "),";
		}
		cout << endl;
		cout << "entry point: " << "(" << stair.entry.x << "," 
			<< stair.entry.y << ")" << endl;
	}
}

int main() {
	// ensure test.data is in the same directory of current one.
	freopen("test.data", "r", stdin);

	ReadEntryPoint();
	DumpEntryPoint();
	ReadOutWalls();
	DumpOutWalls();
	ReadRooms();
	DumpRooms();
	ReadElevators();
	DumpElevators();
	ReadStairs();
	DumpStairs();

	DistributeNodes();
	BuildPath();

	BestPath();

	return 0;
}

void update_charges();

double calc_force( int, int, int );
#define phy_const_k 8987.551787 // k is in ( N * m^2 )/( mC^2 )




/*
sign: 0 = negative, 1 = positive
charge in milliCoulombs 	(mC)
position in meters 			(m)
speed in meters/second  	(m/s)
mass in kilograms 			(kg) if mass is 0, object is fixed.

*/
struct point_charge
{
	double charge, position[2], speed[2], mass;
	short int exists;
	
} charges[MAX_CHARGES];



SDL_Surface* detect_sign( int charge_numb )
{
	if(charge_numb < 0 || charge_numb >= MAX_CHARGES)
		return NULL;
	
	if( charges[charge_numb].charge < 0)
		return ele;
	else if(charges[charge_numb].charge > 0)
		return pro;
	else
		return nue;
}


void setup_charges()
{
	srand(time(NULL));
	number_of_used_charges = 199;
	
	int i;
	for(i = 0; i < number_of_used_charges; i++){
		charges[i].charge = (rand() % 301) - 150;
		charges[i].position[0] = rand() % SCREEN_WIDTH;
		charges[i].position[1] = rand() % SCREEN_HEIGHT;
		charges[i].speed[0] = (rand() % 1001) - 500;
		charges[i].speed[1] = (rand() %3400) + 3000;
		charges[i].mass = (rand() % 10) + 1;
		charges[i].exists = 1;
	}
	
	
	/*
	charges[].charge = 
	charges[].position[0] = 
	charges[].position[1] = 
	charges[].speed[0] = 
	charges[].speed[1] = 
	charges[].mass = 
	charges[].exists = 1;
	*/
	
	frame(0);
}



void update_charges()
{
	char message[50];
	char number[10];
	
	//print time elapsed
	strcpy(message, "Time: ");
	strcat(message, itoa(time_el, number, 10) );
	strcat(message, ".");
	//put the decimal parts of decimal into the integer part of the number.
	int time_decimal = 1000 * time_el;
	time_decimal %= 1000;
	if(time_decimal < 1000)
	{
		strcat(message, "0");
		if(time_decimal < 100)
		{
			strcat(message, "0");
			if(time_decimal < 10)
				strcat(message, "0");
		}
	}
	strcat(message, itoa(time_decimal, number, 10) );
	text = TTF_RenderText_Blended(font, message, textColor);
	apply_surface(10, SCREEN_HEIGHT - 25, text, screen);
	
	//print charge and info
	int i;
	for(i = 0; i < number_of_used_charges; i++)
	{
		if(current_charge == i)
		{
			//particle charge
			strcpy(message, "Charge: ");
			strcat( message, itoa(charges[i].charge, number, 10) );
			strcat(message, " mC");
			text = TTF_RenderText_Blended(font, message, textColor);
			apply_surface(10, 0, text, screen);
			//particle mass
			strcpy(message, "Mass: ");
			strcat( message, itoa(charges[i].mass, number, 10) );
			strcat(message, " kg");
			text = TTF_RenderText_Blended(font, message, textColor);
			apply_surface(10, 25, text, screen);
		}
		//only display the charge if it exists
		if(charges[i].exists)
		{
			//apply the selected.png to the screen behind the current charge if the ith charge is the one selected by the user
			if(i == current_charge)
				apply_surface(charges[i].position[0]-12, charges[i].position[1]-12, clicked, screen);
			//apply charge i to the screen
			apply_surface(charges[i].position[0] - 10, charges[i].position[1] - 10, detect_sign(i), screen);
		}
		if     (charges[i].position[0] > SCREEN_WIDTH)  charges[i].position[0] -= SCREEN_WIDTH;
		else if(charges[i].position[0] < 0)             charges[i].position[0] += SCREEN_WIDTH;
		if     (charges[i].position[1] > SCREEN_HEIGHT) charges[i].position[1] -= SCREEN_HEIGHT;
		else if(charges[i].position[1] < 0)             charges[i].position[1] += SCREEN_HEIGHT;
	}
}



/* returns -1 if there no charge is selected

*/
int get_charge_number(int x, int y)
{
	int i, clicked_the_current_charge = -1;
	
	for(i = 0; i < number_of_used_charges; i++)
	{
		if( x < charges[i].position[0] + 10 && x > charges[i].position[0] - 10 && y < charges[i].position[1] + 10 && y > charges[i].position[1] - 10 )
		{
			//if the user clicked a charge that had already been clicked,
			if( i == current_charge )
			{
				//record
				clicked_the_current_charge = i;
				continue;
			}
			//the user clicked the ith charged particle
			return i;
		}
	}
	//the user clicked the ith charged particle
	if(clicked_the_current_charge+1)
		return clicked_the_current_charge;
	return -1;
}

void get_current_charge(int x, int y)
{
	int i = get_charge_number(x, y);
	current_charge = i;
	//update all charges without calculating any physics
	frame(0);
}


void toggle_charge( int x, int y )
{
	//get charge that you clicked, but don't switch to that charge
	int i = get_charge_number(x, y);
	charges[i].charge *= -1.00;
	//update all charges without calculating any physics
	frame(0);
}




/*

sign: 0 = negative, 1 = positive
charge in milliCoulombs 	(mC)
position in meters 			(m)
speed in meters/second  	(m/s)
mass in kilograms 			(kg) if mass is 0, object is fixed.

struct point_charge
{
	short int sign;
	double charge position[2], speed, direction, mass;
	
	
	
	
} charges[MAX_CHARGES];

*/
/*
k = 8987.551787 ( N * m^2 )/( mC^2 )


*/
void calc_charge_physics()
{
	double acceleration[2];
	int i, j;
	double netForce[MAX_CHARGES][2];
	//calculate all forces
	for(i = 0; i < number_of_used_charges; i++)
	{
		//make the net force acting on the chraged particle start as 0.
		netForce[i][0] = netForce[i][1] = 0;
		//calculate net force and apply that force on the charged particle only if it has mass
		if(charges[i].mass)
		{
			for(j = 0; j < number_of_used_charges; j++)
			{
				//the charges particle has no net force on itslef :P
				if(j == i) continue;
				//calc the force of charge j on charge i (x comp) and add it to netForce[0]
				netForce[i][0] += calc_force(0, j, i);
				//calc the force of charge j on charge i (y comp) and add it to netForce[1]
				netForce[i][1] += calc_force(1, j, i);
			}
		}
	}
	for(i = 0; i < number_of_used_charges; i++)
	{
		//accel in both x and y directions
		acceleration[0] = netForce[i][0] / charges[i].mass;
		acceleration[1] = netForce[i][1] / charges[i].mass;
		//add/subtract from speed based on accel for time time_inc
		charges[i].speed[0] += acceleration[0] * time_inc;
		charges[i].speed[1] += acceleration[1] * time_inc;
		//add/subtract position based on speed
		charges[i].position[0] += charges[i].speed[0] * time_inc;
		charges[i].position[1] += charges[i].speed[1] * time_inc;
	}
}


/*
at the moment, when a particle is moving fast, it has less itterations to calculate the force acting on it.
in short, when a particle is moving fast, the other particles affect it less. this is a problem.
we need to tie the number of force, accel, speed, and position calculations somehow to how far the particle has traveled
*/

//i is the charge being acted on by charge j
double calc_force( int component, int j, int i )
{
	
	//only calculate the force if the particle exists
	if(charges[i].exists == 0 || charges[j].exists == 0) return 0.00;
	
	int sign[2];
	double momentum[2]; // 0 = x comp, 1 = y comp
	double diff[2];		// 0 = x comp, 1 = y comp
	double distance[3];	// 0 = x comp, 1 = y comp, 2 = real distance
	double force[3];	// 0 = x comp, 1 = y comp, 2 = real force
	//calc rectangular coordinates
	distance[0] = charges[j].position[0] - charges[i].position[0];
	distance[1] = charges[j].position[1] - charges[i].position[1];
	
	//calc the distance between the two charges.
	distance[2] = sqrt(distance[0]*distance[0] + distance[1]*distance[1]);
	
	//perfectly inelastic collision (the two things become 1)
	if( distance[2] < 9 )
	{
		if ( current_charge == j ) current_charge = i;
		//if the particle has a collision with a stationary particle
		if(charges[j].mass == 0)
		{
			//charge i no longer exists. it gets absorbed by charge j.
			charges[i].exists = 0;
			//the charges are added together
			charges[j].charge += charges[i].charge;
			return 0.00;
		}
		//j gets absorbed into i. therefore, we do not need j anymore.
		charges[j].exists = 0;
		
		//get momentum
		momentum[0] = charges[i].speed[0] * charges[i].mass + charges[j].speed[0] * charges[j].mass;
		momentum[1] = charges[i].speed[1] * charges[i].mass + charges[j].speed[1] * charges[j].mass;
		
			//modify the surviving particle
		
		//add the two chrages
		charges[i].charge += charges[j].charge;
		
		//i absorbs mass of j
		charges[i].mass += charges[j].mass;
		
		//get new speed determined by momentum of both i and j pre-collision
		charges[i].speed[0] = momentum[0] / charges[i].mass;
		charges[i].speed[1] = momentum[1] / charges[i].mass;
		
		//get difference in x position and y posotion of the two particles.
		diff[0] = charges[j].position[0] - charges[i].position[0];
		diff[0] /= 2;
		diff[1] = charges[j].position[1] - charges[i].position[1];
		diff[1] /= 2;
		//set new position as the smaller position + 
		charges[i].position[0] = charges[i].position[0] + diff[0];
		charges[i].position[1] = charges[i].position[1] + diff[1];
		return 0.00;
	}
	
	//only calculate the force of the electric field if there is a charge on both of the particles
	if(charges[i].charge == 0 || charges[j].charge == 0) return 0.00;
	
	//calc the total force along the line connecting the two forces
	force[2] = phy_const_k * ( (charges[j].charge * charges[i].charge) / (distance[2] * distance[2]) );
	if(force[2] < 0) force[2] *= -1.00;
	
	//force in the component direction equals the total force times the ratio of the distance in that direction over the total distance.
	force[component] = force[2] * distance[component] / distance[2];
	
	if(charges[i].charge > 0)
	sign[0] = 1;
	else
	sign[0] = 0;
	if(charges[j].charge > 0)
	sign[1] = 1;
	else
	sign[1] = 0;
	if(sign[0] == sign[1]) force[component] *= -1.00;
	
	return force[component];
}



void create_new_charge(int x, int y)
{
	//get a shorter variable name (n) for number_of_used_charges
	int n = number_of_used_charges;
	if(n >= MAX_CHARGES)
	{
		//tell user that there are too many charges
		return;
	}
	charges[n].charge = 0;
	charges[n].speed[0] = 0;
	charges[n].speed[1] = 0;
	charges[n].position[0] = x;
	charges[n].position[1] = y;
	charges[n].exists = 1;
	charges[n].mass = 1;
	
	current_charge = n;
	number_of_used_charges++;
	frame(0);
}



void modify_charge_charge(int modify)
{
	if(current_charge == -1) return;
	
	charges[current_charge].charge += modify;
	frame(0);
}

//deletes the charge at x, y
void delete_charge(int x, int y)
{
	//if invalid coordinates were given, delete the current charge
	if(x < 0 || y < 0)
	{
		//only remove the charge if the charge[current_charge] is a valid element of the charges array.
		if(current_charge < 0 || current_charge >= MAX_CHARGES) return;
		charges[current_charge].exists = 0;
		frame(0);
		return;
	}
	//load the current charge into n
	int n = get_charge_number(x, y);
	
	if(n+1)
	charges[n].exists = 0;
	frame(0);
}

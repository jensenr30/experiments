
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
	double a, b;
	a = 2000;
	b = 100;
	
	number_of_used_charges = 14;
	
	charges[0].charge = a;
	charges[0].position[0] = 300;
	charges[0].position[1] = 300;
	charges[0].speed[0] = 0;
	charges[1].speed[1] = 0;
	charges[0].mass = 0;
	charges[0].exists = 1;
	
	charges[1].charge = a;
	charges[1].position[0] = 250;
	charges[1].position[1] = 400;
	charges[1].speed[0] = 0;
	charges[1].speed[1] = 0;
	charges[1].mass = 0;
	charges[1].exists = 1;
	
	charges[2].charge = a;
	charges[2].position[0] = 300;
	charges[2].position[1] = 500;
	charges[2].speed[0] = 0;
	charges[2].speed[1] = 0;
	charges[2].mass = 0;
	charges[2].exists = 1;
	
	charges[3].charge = a;
	charges[3].position[0] = 400;
	charges[3].position[1] = 550;
	charges[3].speed[0] = 0;
	charges[3].speed[1] = 0;
	charges[3].mass = 0;
	charges[3].exists = 1;
	
	charges[4].charge = a;
	charges[4].position[0] = 500;
	charges[4].position[1] = 500;
	charges[4].speed[0] = 0;
	charges[4].speed[1] = 0;
	charges[4].mass = 0;
	charges[4].exists = 1;
	
	charges[5].charge = a;
	charges[5].position[0] = 550;
	charges[5].position[1] = 400;
	charges[5].speed[0] = 0;
	charges[5].speed[1] = 0;
	charges[5].mass = 0;
	charges[5].exists = 1;
	
	charges[6].charge = a;
	charges[6].position[0] = 500;
	charges[6].position[1] = 300;
	charges[6].speed[0] = 0;
	charges[6].speed[1] = 0;
	charges[6].mass = 0;
	charges[6].exists = 1;
	
	charges[7].charge = a;
	charges[7].position[0] = 400;
	charges[7].position[1] = 250;
	charges[7].speed[0] = 0;
	charges[7].speed[1] = 0;
	charges[7].mass = 0;
	charges[7].exists = 1;
	
	charges[8].charge = b;
	charges[8].position[0] = 450;
	charges[8].position[1] = 400;
	charges[8].speed[0] = 0;
	charges[8].speed[1] = 0;
	charges[8].mass = 1;
	charges[8].exists = 1;
	
	charges[9].charge = b;
	charges[9].position[0] = 400;
	charges[9].position[1] = 450;
	charges[9].speed[0] = 400;
	charges[9].speed[1] = 0;
	charges[9].mass = 1;
	charges[9].exists = 1;
	
	charges[10].charge = b;
	charges[10].position[0] = 350;
	charges[10].position[1] = 450;
	charges[10].speed[0] = -400;
	charges[10].speed[1] = 0;
	charges[10].mass = 1;
	charges[10].exists = 1;
	
	charges[11].charge = b;
	charges[11].position[0] = 350;
	charges[11].position[1] = 400;
	charges[11].speed[0] = -200;
	charges[11].speed[1] = 0;
	charges[11].mass = 1;
	charges[11].exists = 1;
	
	charges[12].charge = b;
	charges[12].position[0] = 400;
	charges[12].position[1] = 400;
	charges[12].speed[0] = 100;
	charges[12].speed[1] = -70;
	charges[12].mass = 1;
	charges[12].exists = 1;
	
	charges[13].charge = b;
	charges[13].position[0] = 325;
	charges[13].position[1] = 325;
	charges[13].speed[0] = -150;
	charges[13].speed[1] = 0;
	charges[13].mass = 1;
	charges[13].exists = 1;
	
	
	
	/*
	charges[].charge = 
	charges[].position[0] = 
	charges[].position[1] = 
	charges[].speed[0] = 
	charges[].speed[1] = 
	charges[].mass = 
	charges[].exists = 1;
	*/
	
	//make the screen white
    white_screen();
    //updates the charges
    update_charges();
    //Update the screen
	SDL_Flip( screen );
}



void update_charges()
{
	int i;
	for(i = 0; i < number_of_used_charges; i++)
	{
		//only display the charge if it exists
		if(charges[i].exists)
		{
			apply_surface(charges[i].position[0] - 10, charges[i].position[1] - 10, detect_sign(i), screen);
		}
	}
}



int check_mouse_click(int current_charge, int x, int y)
{
	int i, clicked_the_current_charge = -1;
	for(i = 0; i < number_of_used_charges; i++)
	{
		if( x < charges[i].position[0] + 10 && x > charges[i].position[0] - 10 && y < charges[i].position[1] + 10 && y > charges[i].position[1] - 10 )
		{
			if( i == current_charge )
			{
				clicked_the_current_charge = i;
				continue;
			}
			//display clearly which charged particle the user has clicked.
			white_screen();
			update_charges();
			apply_surface(charges[i].position[0]-12, charges[i].position[1]-12, clicked, screen);
			apply_surface(charges[i].position[0]-10, charges[i].position[1]-10, detect_sign(i), screen);
			SDL_Flip(screen);
			//the user clicked the ith charged particle
			return i;
		}
	}
	//if the user clicked the current charge and there were no other near charges,
	if(clicked_the_current_charge+1)
	{
		//display clearly which charged particle the user has clicked.
		white_screen();
		update_charges();
		apply_surface(charges[clicked_the_current_charge].position[0]-12, charges[clicked_the_current_charge].position[1]-12, clicked, screen);
		apply_surface(charges[clicked_the_current_charge].position[0]-10, charges[clicked_the_current_charge].position[1]-10, detect_sign(clicked_the_current_charge), screen);
		SDL_Flip(screen);
		//the user clicked the ith charged particle
		return clicked_the_current_charge;
	}
	
	//the user didn't click any charged particle
	return -1;
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
	double time_el = 0.0005; // one millisecond of simulation
	
	double acceleration[2];
	int i, j;
	double netForce[2];
	for(i = 0; i < number_of_used_charges; i++)
	{
		//make the net force acting on the chraged particle start as 0.
		netForce[0] = netForce[1] = 0;
		//calculate net force and apply that force on the charged particle only if it has mass
		if(charges[i].mass)
		{
			for(j = 0; j < number_of_used_charges; j++)
			{
				//the charges particle has no net force on itslef :P
				if(j == i) continue;
				//calc the force of charge j on charge i (x comp) and add it to netForce[0]
				netForce[0] += calc_force(0, j, i);
				//calc the force of charge j on charge i (y comp) and add it to netForce[1]
				netForce[1] += calc_force(1, j, i);
			}
			//accel in both x and y directions
			acceleration[0] = netForce[0] / charges[i].mass;
			acceleration[1] = netForce[1] / charges[i].mass;
			//add/subtract from speed based on accel for time time_el
			charges[i].speed[0] += acceleration[0] * time_el;
			charges[i].speed[1] += acceleration[1] * time_el;
			//add/subtract position based on speed
			charges[i].position[0] += charges[i].speed[0] * time_el;
			charges[i].position[1] += charges[i].speed[1] * time_el;
		}
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




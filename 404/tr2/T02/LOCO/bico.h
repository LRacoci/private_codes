/**************************************************************** 
 * Description: Uoli Control Application Programming Interface.
 *
 * Authors: Edson Borin (edson@ic.unicamp.br)
 *
 * Date: 2015
 ***************************************************************/
#ifndef BICO
#define BICO

/**************************************************************/
/* Motors                                                     */
/**************************************************************/

/* 
 * Sets motor speed. 
 * Parameters: 
 *   id: the motor id (0 for left motor, 1 for right motor)
 *   speed: the motor speed (Only the last 6 bits are used)
 * Returns:
 *   void
 */
void set_motor_speed(unsigned char id, unsigned char speed);

/* 
 * Sets both motors speed. 
 * Parameters: 
 *   spd_m0: the speed of motor 0 (Only the last 6 bits are used)
 *   spd_m1: the speed of motor 1 (Only the last 6 bits are used)
 * Returns:
 *   void
 */
void set_motors_speed(unsigned char spd_m0, unsigned char spd_m1);

/**************************************************************/
/* Sonars                                                     */
/**************************************************************/
/* 
 * Reads one of the sonars.
 * Parameter: 
 *   dist: pointer to variable that will receive the distance.
 *   sonar_id: the sonar id (ranges from 0 to 15).
 * Returns:
 *   void
 */
void read_sonar(unsigned char sonar_id, unsigned short* dist);

/* 
 * Reads all sonars at once.
 * Parameter: 
 *   sonars: array of 16 unsigned integers. The distances are stored
 *   on the array.
 * Returns:
 *   void
 */
void read_sonars(unsigned int *distances);

#endif // API_ROBOT2_H
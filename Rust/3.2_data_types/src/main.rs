fn main() {
    let guess: usize = "42".parse().expect("Not a number!");
    println!("guess = {guess}.");
    
    let _x = 2.0;
    let _y: f32 = 3.0;
    // addition
    let _sum = 5 + 10;

    // subtraction
    let _difference = 95.5 - 4.3;

    // multiplication
    let _product = 4 * 30;

    // division
    let _quotient = 56.7 / 32.2;
    let _truncated = -5 / 3; // Results in -1

    // remainder
    let _remainder = 43 % 5;

    // bool
    let _t = true;
    let _f: bool = false;

    // char
    let _c = 'z';
    let _ce: char = 'C';
    let moon = '🌚';
    println!("{moon} 🌙");

    // tuple
    let tup = (500, 3.1415926, 'c', "String");

    let (i, f, c, s) = tup;
    println!("i is {i}");
    println!("f is {f}");
    println!("c is {c}");
    println!("s is {s}");
    println!("tuple 3rd element is {}",tup.2);
    let _empty_tuple = ();

    // array
    let _a = [1, 2, 3, 4, 5];
    let months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
    println!("Number of months = {}", months.len());
    
    // // try to cause a stack overflow
    // const ARRAY_LENGTH: usize = 125000;
    // // creates an array initialized to 0.
    // let _a:[usize; ARRAY_LENGTH] = [0; ARRAY_LENGTH];
    // println!("Approx stack data is: {} MB",
    //     ARRAY_LENGTH as f64 * 8.0 / (1024.0*1024.0));
}

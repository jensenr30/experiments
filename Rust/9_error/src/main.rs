fn main() {
    // crash the program
    //panic!("crash and burn");

    // access outside bounds of a vector
    let v = vec![1, 2, 3];
    println!("{}", v[99]);
}
fn main() {
    let mut v2 = vec![1, 2, 3];
    v2.push(4);
    // v2.push(5);
    // v2.push(6);
    // v2.push(7);
    let third: &i32 = &v2[2];
    println!("The third element is {third}.");
    let fourth: &i32 = &v2[3];
    println!("The fourth element is {fourth}.");
    let third: Option<&i32> = v2.get(2);
    match third {
        Some(third) =>  println!("The third element is {third}."),
        None =>         println!("There is no third element."),
    }

    // compile time error due to mutable borrow after immutable borrow
    // let mut v = vec![1, 2, 3, 4, 5];
    // let first = &v[0];
    // v.push(6);
    // println!("The first element is {first}.");

    // iterating over the values in a vector
    let mut v = vec![100, 32, 57];
    for i in &mut v {
        *i += 50;
        println!("{}", *i);
    }

    enum SpreadsheetCell {
        Int(i32),
        Float(f64),
        Text(String),
    }
    let row = vec![
        SpreadsheetCell::Int(3),
        SpreadsheetCell::Text(String::from("blue")),
        SpreadsheetCell::Float(3.1415926),
    ];
    for r in row {
        match r {
            SpreadsheetCell::Int(x) =>   println!("{x}"),
            SpreadsheetCell::Float(x) => println!("{x}"),
            SpreadsheetCell::Text(x)  => println!("{x}"),
        }
    }

    // Creating a New String
    let mut s = String::new();
    let slice = "copy of a ";
    for i in 0..4 {
        s.push_str(slice);
    }
    println!("{}",s);
}

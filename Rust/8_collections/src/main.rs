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
    println!("s is {s}");

    let data = "string literal";
    let s = data.to_string();
    println!("String created from {s}");
    let s = "string literal can be directly converted to String.".to_string();
    println!("{s}");
    let mut s = String::from("Another method to create a String from literal");
    println!("{s}");
    s.push_str(" lets push some characters onto that string!");
    println!("{s}");
    // lets push a String onto itself.  We need to clone() the String, because
    // otherwise we would be passing both a mutable and immutable reference of
    // the same String to the push_str function which is illegal.
    s.push_str(&s.clone());
    println!("{s}");
    // concatenation with the + operator
    let s1 = String::from("Hello, ");
    let s2 = String::from("world!");
    let s3 = s1 + &s2;
    println!("{s3}");
    let sl1 = "string literal 1. ";
    let sl2 = "string literal 2.";
    let s3 = sl1.to_string() + sl2;
    println!("{s3}");

    // Storing Keys with Associated Values in Hash Maps
    use std::collections::HashMap;
    let mut scores: HashMap<String, i64> = HashMap::new();
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 50);
    let team_name = String::from("Blue");
    let score = scores.get(&team_name).copied().unwrap_or(0);
    println!("{team_name} scored {score} points.");
    // iterate over every key, value pair
    for (key, value) in &scores {
        println!("{key}: {value}");
    }

    // Adding a Key and Value Only if a Key Isn't Present
    let mut scores2 = HashMap::new();
    scores2.insert(String::from("Blue"), 20);
    scores2.entry(String::from("Yellow")).or_insert(60);
    scores2.entry(String::from("Blue")).or_insert(60);
    println!("{:?}", scores2);

    // Updating a value Based on the Old Value
    let text = "Hello world wonderful world";
    let mut word_hist = HashMap::new();
    for word in text.split_whitespace() {
        let count = word_hist.entry(word).or_insert(0);
        *count += 1;
    }
    println!("{:?}", word_hist);
}

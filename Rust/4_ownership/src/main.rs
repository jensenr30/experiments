fn main() {
    let mut  s1 = String::from("hello");
    s1.push_str(", world!");
    let mut s2 = s1.clone();
    println!("{s1}");
    println!("{s2}");
    s1.push_str(" String 1 here.");
    s2.push_str(" String 2 here.");
    println!("{s1}");
    println!("{s2}");
    modify_and_print(&mut s1);
    modify_and_print(&mut s2);
    let len1 = calculate_length(&s1);
    let len2 = calculate_length(&s2);
    println!("s1 is {len1} characters long.");
    println!("s2 is {len2} characters long.");

    let s = String::from("Hello world!");
    println!("s = {s}");
    let fword = get_first_word(&s);
    println!("first word = {fword}");
    s2 = s.clone();
    s2.push_str(" Hello again!");
    println!("s2 = {s2}");
    let slice1 = &s[0..5];
    let slice2 = &s[6..];
    println!("slice1 = {slice1}");
    println!("slice2 = {slice2}");
    // test array slices
    let a = [0, 10, 20, 30, 40];
    let aslice = &a[2..=3];
    assert_eq!(aslice, &[20, 30]);
}

fn modify_and_print(s: &mut String) {
    *s += " concatenated!";
    println!("{}", s);
}

fn calculate_length(s: &String) -> usize {
    return s.len();
}

fn get_first_word(s: &str) -> &str {
    let bytes = s.as_bytes();
    for (i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[0..i];
        }
    }
    return &s[..];
}
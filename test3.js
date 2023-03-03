export function do_run(path) {
    print("Hi.");
    print(MyPkg.f());

    // File doesn't exist
    var f = new File(path);
}

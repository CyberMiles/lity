contract test {
    function f() public {
        ufixed256x1 a = 1/3; a;
    }
}
// ----
// TypeError: (50-69): Type rational_const 1 / 3 is not implicitly convertible to expected type ufixed256x1.

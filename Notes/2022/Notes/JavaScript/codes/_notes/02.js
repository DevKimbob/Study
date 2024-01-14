"use strict";
if(0){  // easier code testing porposes

// 2.2.
alert('Hello')
alert('Hello');  // prefers this one

// single
/*
multiple
*/

// 2.3.
// "use strict";  // when not using class or module

// 2.4.
let message = 'Hello';  // new version
var old = 'old';  // old version
const MAX = 100;

// 2.5.
alert(1 / 0);  // Infinity
alert(Infinity);
alert('NaN' / 2);  // Not a Number

const bigInt = 1234567890n;  // BigInt, ends with n

let str = "Hello"  // ""
let str2 = 'hello'  // ''
let phrase = `embeds! ${str}`  // `` embeds!
alert(phrase);

let amIHungry = true;
let yoyo = false;
let isGrater = 4 > 1;  // false

let age = null;  // a bit different from other languages

let undefined1;
alert(undefined1);  // undefined
let undefined2 = undefined;  // do not recommend, null is better

// object, symbol : passed

alert(typeof str);
alert(typeof null);  // null is not a object. language error

// 2.6.
alert("alert");

let result = prompt("prompt", 100);  // 100 : default value for Cancel/<ESC>
alert(`result : ${result}, default : 100`);

let result2 = confirm("confirm");  // true or false
alert(result2);

// 2.7.
let bool1 = true;
alert(typeof bool1);
bool1 = String(bool1);
alert(typeof bool1);  // String

alert("6"/"2");
let str3 = "123";
alert(typeof str3);
let num = Number(str3);
alert(typeof num);  // Number
str3 = Number(str3);
alert(str3);  // 123

let num2 = Number("NaN");
alert(num2);  // NaN

alert(Number("   123   "));  // 123
alert(Number("123z"));  // NaN : z
alert(Number(true));  // 1
alert(Number(false));  // 0

alert(Boolean(1));  // ture
alert(Boolean(0));  // false
alert(Boolean("text"));  // true
alert(Boolean(" "));  // false
alert(Boolean("0"));  // ture

}
// 2.8.

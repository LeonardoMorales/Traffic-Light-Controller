var firebaseConfig = {
  apiKey: "YOUR_API_KEY",
  authDomain: "YOUR_AUTH",
  databaseURL: "YOUR_DB_URL",
  projectId: "YOUR_PROJECT_ID",
  storageBucket: "YOUR_STORAGE_BUCKET",
  messagingSenderId: "YOUR_MESSAGING_SENDER_ID",
  appId: "YOUR_API_ID"
};
// Initialize Firebase
firebase.initializeApp(firebaseConfig);

let dbTrafficLight = firebase.database().ref("ESP32/Traffic-Light/Value");

$(document).ready(function () {
  $("button").click(function () {
    var color = [];
    $.each($("input[name='gridRadios']:checked"), function () {
      color = $(this).val();
    });

    dbTrafficLight.set(color);
    console.log(color);
  });
});

$("#enviar").click(function (event) {

}); 

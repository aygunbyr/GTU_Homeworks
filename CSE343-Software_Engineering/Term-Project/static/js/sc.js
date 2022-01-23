//global variables
var monthEl = $(".c-main");
var dataCel = $(".c-cal__cel");
var dataHour = $(".hour_cell");
var dateObj = new Date();
var month = dateObj.getUTCMonth() + 1;
var day = dateObj.getUTCDate();
var year = dateObj.getUTCFullYear();
var activeDay = null;
var activeMonth = null;

var reservedHours = [];
var counterReservedHours = 1;

var monthText = [
  "January",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December",
];
var indexYear = 0;
var indexMonth = month;
var inputDate = $(this).data();

$(document).on("click", ".hour_cell", function () {
  var th = $(this).data().hours.slice(0, 2);

  for (var i = 0; i < counterReservedHours; i++) {
    if (i + 1 == counterReservedHours && reservedHours[i] != th) {
      counterReservedHours++;
      reservedHours[i] = th;
      break;
    } else if (reservedHours[i] == th) {
      reservedHours.splice(reservedHours.indexOf(th), 1);
      counterReservedHours--;
      break;
    }
  }
  $(this).toggleClass("isSelected");
});

function bookFunction() {
  if (activeDay != null && counterReservedHours == 2) {
    $(".wrapper-2").addClass("wrapper-2-active");
    $(".wrapper").addClass("make-blur");
    $("header").addClass("make-blur");

    document.getElementById("id_thedate").value =
      year + "-" + activeMonth + "-" + activeDay;

    document.getElementById("id_hour").value = reservedHours[0];

    document.getElementById("id_trainer_id").value = document
      .getElementById("trainerid")
      .textContent.slice(11);

    document.getElementById("id_customer_id").value = document
      .getElementById("userid")
      .textContent.slice(8);
  }
}
window.addEventListener("load", () => {
  document.querySelector("#close").addEventListener("click", (e) => {
    $(".wrapper-2").removeClass("wrapper-2-active");
    $(".wrapper").removeClass("make-blur");
    $("header").removeClass("make-blur");

    document.getElementById("id_thedate").value = NULL;
  });
});

dataCel.on("click", function () {
  var thisEl = $(this);
  var thisDay = $(this).attr("data-day").slice(8);
  var thisMonth = $(this).attr("data-day").slice(5, 7);
  activeDay = thisDay;
  activeMonth = thisMonth;
  $(".c-aside__num").text(thisDay);
  $(".c-aside__month").text(monthText[thisMonth - 1]);
  $(".c-aside__year").text(dateObj.getUTCFullYear() + indexYear);
  xhttp(thisDay, thisMonth);

  dataCel.removeClass("isSelected");
  thisEl.addClass("isSelected");
});

//function for move the months
function moveNext(fakeClick, indexNext) {
  for (var i = 0; i < fakeClick; i++) {
    $(".c-main").css({
      left: "-=100%",
    });
    $(".c-paginator__month").css({
      left: "-=100%",
    });
    switch (true) {
      case indexNext:
        indexMonth += 1;
        break;
    }
  }
}

function movePrev(fakeClick, indexPrev) {
  for (var i = 0; i < fakeClick; i++) {
    $(".c-main").css({
      left: "+=100%",
    });
    $(".c-paginator__month").css({
      left: "+=100%",
    });
    switch (true) {
      case indexPrev:
        indexMonth -= 1;
        break;
    }
  }
}

//months paginator
function buttonsMonthPaginator(buttonId, mainClass, monthClass, next, prev) {
  switch (true) {
    case next:
      $(buttonId).on("click", function () {
        if (indexMonth >= 2) {
          $(mainClass).css({
            left: "+=100%",
          });
          $(monthClass).css({
            left: "+=100%",
          });
          indexMonth -= 1;
        }

        return indexMonth;
      });
      break;
    case prev:
      $(buttonId).on("click", function () {
        if (indexMonth <= 11) {
          $(mainClass).css({
            left: "-=100%",
          });
          $(monthClass).css({
            left: "-=100%",
          });
          indexMonth += 1;
        }
        return indexMonth;
      });
      break;
  }
}

buttonsMonthPaginator("#next", monthEl, ".c-paginator__month", false, true);
buttonsMonthPaginator("#prev", monthEl, ".c-paginator__month", true, false);

//months paginator
function buttonsYearPaginator(buttonId, monthClass, next, prev) {
  switch (true) {
    case next:
      $(buttonId).on("click", function () {
        if (indexYear >= 1) {
          $(monthClass).css({
            left: "+=100%",
          });
          indexYear -= 1;
        }
        year = dateObj.getUTCFullYear() + indexYear;
        $(".c-aside__year").text(dateObj.getUTCFullYear() + indexYear);

        return indexYear;
      });
      break;
    case prev:
      $(buttonId).on("click", function () {
        if (indexYear <= 1) {
          $(monthClass).css({
            left: "-=100%",
          });
          indexYear += 1;
        }
        year = dateObj.getUTCFullYear() + indexYear;
        $(".c-aside__year").text(dateObj.getUTCFullYear() + indexYear);

        return indexYear;
      });
      break;
  }
}

buttonsYearPaginator("#nextYear", ".c-paginator__year", false, true);
buttonsYearPaginator("#prevYear", ".c-paginator__year", true, false);

//launch function to set the current month
moveNext(indexMonth - 1, false);
//fill the year

document.getElementById("firstY").innerHTML = dateObj.getUTCFullYear();
document.getElementById("secondY").innerHTML = dateObj.getUTCFullYear() + 1;
document.getElementById("thirdY").innerHTML = dateObj.getUTCFullYear() + 2;

//fill the sidebar with current day
$(".c-aside__num").text(day);
$(".c-aside__month").text(monthText[month - 1]);
$(".c-aside__year").text(year);

function xhttp(day, month) {
  // Create an XMLHttpRequest object
  const xhttp = new XMLHttpRequest();
  var hourArray;
  var trainer_id = window.location.href.split(
    "http://127.0.0.1:8000/payment/charge/"
  );
  // Define a callback function
  xhttp.onload = function () {
    var parser, xmlDoc;
    var text = this.responseText;

    parser = new DOMParser();

    xmlDoc = parser.parseFromString(text, "text/xml");

    hourArray = xmlDoc.getElementsByTagName("item");

    booking_hours(hourArray);
  };

  // Send a request-
  xhttp.open(
    "GET",
    "http://127.0.0.1:8000/trainer/reservationInfo/" +
      trainer_id[1].slice(0, 1) +
      "/" +
      year +
      "-" +
      month +
      "-" +
      day +
      "/"
  );
  xhttp.send();
}

function booking_hours(hourArray) {
  var table;

  for (var i = 0; i < hourArray.length; i++) {
    if (parseInt(hourArray[i].childNodes[0].nodeValue) < 9)
      table +=
        "<div data-hours='0" +
        hourArray[i].childNodes[0].nodeValue +
        ".00-0" +
        (parseInt(hourArray[i].childNodes[0].nodeValue) + 1) +
        ".00' class='hour_cell'>" +
        "<p>" +
        "0" +
        hourArray[i].childNodes[0].nodeValue +
        ".00 - 0" +
        (parseInt(hourArray[i].childNodes[0].nodeValue) + 1) +
        ".00" +
        "</p></div>";
    else if (parseInt(hourArray[i].childNodes[0].nodeValue) == 9) {
      table +=
        "<div data-hours='0" +
        hourArray[i].childNodes[0].nodeValue +
        ".00-0" +
        (parseInt(hourArray[i].childNodes[0].nodeValue) + 1) +
        ".00' class='hour_cell'>" +
        "<p>" +
        "0" +
        hourArray[i].childNodes[0].nodeValue +
        ".00 - " +
        (parseInt(hourArray[i].childNodes[0].nodeValue) + 1) +
        ".00" +
        "</p></div>";
    } else {
      table +=
        "<div data-hours='" +
        hourArray[i].childNodes[0].nodeValue +
        ".00-" +
        (parseInt(hourArray[i].childNodes[0].nodeValue) + 1) +
        ".00' class='hour_cell'>" +
        "<p>" +
        hourArray[i].childNodes[0].nodeValue +
        ".00 - " +
        (parseInt(hourArray[i].childNodes[0].nodeValue) + 1) +
        ".00" +
        "</p></div>";
    }
  }
  if (hourArray.length) {
    console.log("bir seet");
    document.getElementById("hoursList").innerHTML = table.slice(9);
  } else document.getElementById("hoursList").innerHTML = null;
}

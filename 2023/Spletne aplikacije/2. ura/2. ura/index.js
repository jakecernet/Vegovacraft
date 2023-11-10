window.addEventListener('scroll', function () {
    var scrollPos = window.pageYOffset || document.documentElement.scrollTop || document.body.scrollTop;

    var scrollToTop = document.getElementById('nav');
    if (scrollPos > 400) {
        scrollToTop.style.opacity = '0';
    } else {
        scrollToTop.style.opacity = '1';
    }
});
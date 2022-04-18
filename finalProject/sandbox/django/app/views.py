import http
from django.shortcuts import render
from django.http import HttpResponse

# Create your views here.


def index(request):
    ctxt = {
        'context': "contextual help from app/views.py ",
    }
    return render(request, 'app/index.html', context=ctxt)

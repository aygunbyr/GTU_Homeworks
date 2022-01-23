from django.db.models.fields import DateField
from django.db.models.query import QuerySet
from django.shortcuts import render, HttpResponse, get_object_or_404, HttpResponseRedirect, Http404
from .models import CalendarEvent, Reservation, Trainer
from .forms import TrainerForm, CommentForm
from django.contrib import messages
from dict2xml import dict2xml
import datetime
from django.contrib.auth.decorators import login_required
from Product.models import Product
from django.core.mail import send_mail
from django.conf import settings
import jwt
import datetime
import requests
import json
import xml.etree.ElementTree as ET

def trainer_index(request):
    print("here")
    trainers = Trainer.objects.all()
    auth_trainer = None
    if request.user.is_authenticated:
        auth_trainer = trainers.filter(User_ID=request.user)

    return render(request, 'trainer/index.html', {'trainers': trainers, 'auth_trainer': auth_trainer})


def trainer_detail(request, id):
    trainer = get_object_or_404(Trainer, id=id)
    product = None
    product = Product.objects.all().first()

    disc_price = product.price * ((100 - product.discount_rate) / 100)

    form = CommentForm(request.POST or None)
    if form.is_valid():
        comment = form.save(commit=False)
        comment.trainer = trainer
        comment.save()
        return HttpResponseRedirect(trainer.get_absolute_url())

    context = {
        'trainer': trainer,
        'form': form,
        'product': product,
        'disc_price': disc_price,
    }

    return render(request, 'trainer/detail.html', context)


def trainer_create(request):
    form = TrainerForm(request.POST or None, request.FILES or None)
    if form.is_valid():
        form.save()
    else:
        form = TrainerForm()
    context = {
        'form': form,
    }
    return render(request, 'trainer/form.html', context)


def trainer_update(request, id):
    if not request.user.is_authenticated:
        return Http404()

    trainer = get_object_or_404(Trainer, id=id)
    print(trainer.User_ID)
    form = TrainerForm(request.POST or None, request.FILES or None, instance=trainer)
    if form.is_valid():
        if request.user == trainer.User_ID:
            form.save()
            messages.success(request, 'Successfully updated!')
            return HttpResponseRedirect(trainer.get_absolute_url())
        else:
            messages.warning(request, 'You can not edit another trainer\'s information.')
            return redirect('trainer:index')
    context = {
        'form': form,
    }
    return render(request, 'trainer/form.html', context)


def trainer_delete(request):
    return HttpResponse('Burası trainer delete sayfası')


def add_calendar_event(request):
    return HttpResponse('Burası trainer delete sayfası')


def is_free_at(trainerId, date, hour):
    dateS = date.split('-')
    dayofweek = datetime.date(int(dateS[0]), int(dateS[1]), int(dateS[2])).weekday()

    isThereTheEvent = CalendarEvent.objects.filter(day_of_week=dayofweek, trainer=trainerId, start_time=hour)

    if (isThereTheEvent):
        rezervations = Reservation.objects.filter(date_time=date, trainer=trainerId)  # id ile query hata hata
        if (rezervations.exists()):
            for res in rezervations:
                print("resssssssssssssS::", res.event.start_time)
                if (res.event.start_time == hour):
                    return False
            return True
        else:
            return True
    else:
        return False





def free__lectures(trainerId, date):
    free_lecs = list()

    for a in range(0, 23):
        isFree = is_free_at(trainerId, date, a)
        print("is free ", a, ":", isFree)
        if (isFree):
            free_lecs.append(a)
    return free_lecs

    dateS = date.split('-')
    print("date::::::", dateS)
    dayofweek = datetime.date(int(dateS[0]), int(dateS[1]), int(dateS[2])).weekday()
    print("dayofweek:", dayofweek)
    events = CalendarEvent.objects.filter(day_of_week=dayofweek, trainer=trainerId)
    print("events::", events)

    free__lecs = list()
    for event in events:
        print("eve::", event)
        if (is_free_at(trainerId, date, event.start_time)):
            free__lecs.append(event)
            print("eventt:::", event)

    return free__lecs

def create_xml(list):
  
        # we make root element
        usrconfig = ET.Element("hours")
  
        # create sub element
        usrconfig = ET.SubElement(usrconfig, "hours")
  
        # insert list element into sub elements
        for user in range(len( list)):
  
                usr = ET.SubElement(usrconfig, "item")
                usr.text = str(list[user])
  
        tree = ET.ElementTree(usrconfig)
        
        return  ET.tostring(usrconfig, encoding="unicode")
        # write the tree into an XML file
        #tree.write("Output.xml", encoding ='utf-8', xml_declaration = True)
# Reservation part


def reservationInfo(request, id, date):
    free_lecs = free__lectures(id, date)

    a = [1, 2]
    data = {"free_lecs": free_lecs
            }

    xml = create_xml(free_lecs)
    print(xml)

    return HttpResponse(str(xml))


@login_required
def reservation(request, id):
    return render(request, 'trainer/calendar.html')
